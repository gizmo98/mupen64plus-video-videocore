// mupen64plus-video-videocore/VCConfig.cpp
//
// Copyright (c) 2016 The mupen64plus-video-videocore Authors

#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "VCConfig.h"
#include "VCUtils.h"
#include "toml.h"

#ifdef __linux__
#include <linux/limits.h>
#endif

#ifdef VC
#include <bcm_host.h>
#endif

#define VC_DEFAULT_DISPLAY_WIDTH        1920
#define VC_DEFAULT_DISPLAY_HEIGHT       1080
#define VC_DEFAULT_DEBUG_DISPLAY        false

static VCConfig sharedConfig = {
    VC_DEFAULT_DISPLAY_WIDTH,
    VC_DEFAULT_DISPLAY_HEIGHT,
    VC_DEFAULT_DEBUG_DISPLAY,
};

VCConfig *VCConfig_SharedConfig() {
    return &sharedConfig;
}

static int VCConfig_GetInt(const toml::Value &topValue, const char *name, int defaultValue) {
    const toml::Value *value = topValue.find(name);
    if (value == nullptr)
        return defaultValue;
    if (!value->is<int>()) {
        std::cerr << "warning: `" << name << "` should be an integer; using the default value." <<
            std::endl;
        return defaultValue;
    }
    return value->as<int>();
}

static bool VCConfig_GetBool(const toml::Value &topValue, const char *name, bool defaultValue) {
    const toml::Value *value = topValue.find(name);
    if (value == nullptr)
        return defaultValue;
    if (!value->is<bool>()) {
        std::cerr << "warning: `" << name << "` should be a Boolean; using the default value." <<
            std::endl;
        return defaultValue;
    }
    return value->as<bool>();
}

static char *VCConfig_GetString(const toml::Value &topValue,
                                const char *name,
                                const char *defaultValue) {
    const toml::Value *value = topValue.find(name);
    if (value == nullptr)
        return strdup(defaultValue);
    if (!value->is<std::string>()) {
        std::cerr << "warning: `" << name << "` should be a string; using the default value." <<
            std::endl;
        return strdup(defaultValue);
    }
    std::string string = value->as<std::string>();
    return strdup(string.c_str());
}

void VCConfig_Read(VCConfig *config) {
#ifdef VC
    unsigned int fb_width;
    unsigned int fb_height;
    bcm_host_init();
    if (graphics_get_display_size(0 /* LCD */, &fb_width, &fb_height) < 0)
        std::cerr << "error: failed to get display size" << std::endl;
    else {
        config->displayWidth = fb_width;
        config->displayHeight = fb_height;
    }
#endif

    char *path = (char *)malloc(PATH_MAX + 1);

    std::ifstream input;
    const char *configHome = getenv("XDG_CONFIG_HOME");
    if (configHome == NULL || configHome[0] == '\0') {
        configHome = ".config";
        const char *home = getenv("HOME");
        if (home == NULL)
            home = ".";
        snprintf(path, PATH_MAX, "%s/.config/mupen64plus/videocore.conf", home);
        input.open(path);
    } else {
        snprintf(path, PATH_MAX, "%s/mupen64plus/videocore.conf", configHome);
        input.open(path);
    }

    if (input.fail()) {
        const char *configDirsLocation = getenv("XDG_CONFIG_DIRS");
        if (configDirsLocation == NULL || configDirsLocation[0] == '\0')
            configDirsLocation = "/etc/xdg";
        char *configDirs = strdup(configDirsLocation);
        do {
            char *configDir = xstrsep(&configDirs, ":");
            if (configDir == NULL) {
                std::cerr << "video warning: `videocore.conf` not found; using defaults." <<
                    std::endl;
                std::cerr << "video warning: try placing `videocore.conf` in " <<
                    "`~/.config/mupen64plus` or wherever `$XDG_CONFIG_HOME` points to" <<
                    std::endl;
                return;
            }
            snprintf(path, PATH_MAX, "%s/mupen64plus/videocore.conf", configDir);
            input.open(path);
        } while (input.fail());
    }
    free(path);

    assert(!input.fail());
    toml::ParseResult parseResult = toml::parse(input);
    if (!parseResult.valid()) {
        std::cerr << "error: failed to parse `videocore.conf`: " << parseResult.errorReason <<
            std::endl;
        exit(1);
    }

    const toml::Value &topValue = parseResult.value;
#ifndef VC
    config->displayWidth = VCConfig_GetInt(topValue, "display.width", VC_DEFAULT_DISPLAY_WIDTH);
    config->displayHeight = VCConfig_GetInt(topValue, "display.height", VC_DEFAULT_DISPLAY_HEIGHT);
#endif
    config->debugDisplay = VCConfig_GetBool(topValue,
                                            "debug.display",
                                            VC_DEFAULT_DEBUG_DISPLAY);
}

