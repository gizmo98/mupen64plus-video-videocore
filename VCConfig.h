// mupen64plus-video-videocore/VCConfig.h
//
// Copyright (c) 2016 The mupen64plus-video-videocore Authors

#ifndef VCCONFIG_H
#define VCCONFIG_H

struct VCConfig {
    int displayWidth;
    int displayHeight;
    bool debugDisplay;
};

VCConfig *VCConfig_SharedConfig();
void VCConfig_Read(VCConfig *config);

#endif

