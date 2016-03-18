ifdef DEBUG
CFLAGS?=-O0 -g
else
CFLAGS?=-O2
endif

CFLAGS+=-Wall -Wno-parentheses -std=c++11
LD=g++
LDFLAGS=
LIBS=

ifeq ($(shell uname -m),armv7l)
    LDLIBS += -ldl
    LDLIBS += -L/opt/vc/lib -lGLESv2 -lEGL
    CFLAGS += -DHAVE_OPENGLES2 -DVC -I/opt/vc/include -I/opt/vc/include/interface/vcos/pthreads -I/opt/vc/include/vmcs_host/linux
    LDFLAGS += -Wl,-Bsymbolic
    LDFLAGS += -Wl,-version-script,$(SRCDIR)/video_api_export.ver
    SHARED = -shared
    SO_EXTENSION = so
    PIC ?= 1
else
    ifeq ($(shell uname -o),Msys)
        LDLIBS+=-lglew32 -lopengl32
        LDFLAGS+=-Wl,-Bsymbolic
        SO_EXTENSION = dll
        PIC ?= 0
    else
        ifeq ($(shell uname),Darwin)
            LDLIBS += -framework OpenGL
            SO_EXTENSION = dylib
            PIC ?= 0
        endif
    endif
endif

# base CFLAGS, LDLIBS, and LDFLAGS
OPTFLAGS ?= -flto
WARNFLAGS ?= -Wall -Wno-parentheses
CFLAGS += $(OPTFLAGS) $(WARNFLAGS) -std=c++11 -ffast-math -fno-strict-aliasing -fvisibility=hidden -I../../src
CXXFLAGS += -Wall -Wno-parentheses -fvisibility-inlines-hidden -std=c++11
LDFLAGS += $(SHARED)

# Since we are building a shared library, we must compile with -fPIC on some architectures
# On 32-bit x86 systems we do not want to use -fPIC because we don't have to and it has a big performance penalty on this arch
ifeq ($(PIC), 1)
  CFLAGS += -fPIC
else
  CFLAGS += -fno-PIC
endif

# test for essential build dependencies
ifeq ($(origin PKG_CONFIG), undefined)
  PKG_CONFIG = $(CROSS_COMPILE)pkg-config
  ifeq ($(shell which $(PKG_CONFIG) 2>/dev/null),)
    $(error $(PKG_CONFIG) not found)
  endif
endif

# test for presence of SDL
ifeq ($(origin SDL_CFLAGS) $(origin SDL_LDLIBS), undefined undefined)
  SDL_CONFIG = $(CROSS_COMPILE)sdl2-config
  ifeq ($(shell which $(SDL_CONFIG) 2>/dev/null),)
    SDL_CONFIG = $(CROSS_COMPILE)sdl-config
    ifeq ($(shell which $(SDL_CONFIG) 2>/dev/null),)
      $(error No SDL development libraries found!)
    else
      $(warning Using SDL 1.2 libraries)
    endif
  endif
  SDL_CFLAGS  += $(shell $(SDL_CONFIG) --cflags)
  SDL_LDLIBS += $(shell $(SDL_CONFIG) --libs)
endif
CFLAGS += $(SDL_CFLAGS)
LDLIBS += $(SDL_LDLIBS)

# set mupen64plus core API header path
ifneq ("$(APIDIR)","")
  CFLAGS += "-I$(APIDIR)"
else
  TRYDIR = ../../../mupen64plus-core/src/api
  ifneq ("$(wildcard $(TRYDIR)/m64p_types.h)","")
    CFLAGS += -I$(TRYDIR)
  else
    TRYDIR = /usr/local/include/mupen64plus
    ifneq ("$(wildcard $(TRYDIR)/m64p_types.h)","")
      CFLAGS += -I$(TRYDIR)
    else
      TRYDIR = /usr/include/mupen64plus
      ifneq ("$(wildcard $(TRYDIR)/m64p_types.h)","")
        CFLAGS += -I$(TRYDIR)
      else
        $(error Mupen64Plus API header files not found! Use makefile parameter APIDIR to force a location.)
      endif
    endif
  endif
endif

# reduced compile output when running make without V=1
ifneq ($(findstring $(MAKEFLAGS),s),s)
ifndef V
	Q_CC  = @echo '    CC  '$@;
	Q_CXX = @echo '    CXX '$@;
	Q_LD  = @echo '    LD  '$@;
endif
endif

# set base program pointers and flags
CC        = $(CROSS_COMPILE)gcc
CXX       = $(CROSS_COMPILE)g++
RM       ?= rm -f
INSTALL  ?= install
MKDIR ?= mkdir -p
COMPILE.c = $(Q_CC)$(CC) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c
COMPILE.cc = $(Q_CXX)$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c
LINK.o = $(Q_LD)$(CXX) $(CXXFLAGS) $(LDFLAGS) $(TARGET_ARCH)

# set installation options
ifeq ($(PREFIX),)
  PREFIX := /usr/local
endif
ifeq ($(SHAREDIR),)
  SHAREDIR := $(PREFIX)/share/mupen64plus
endif
ifeq ($(LIBDIR),)
  LIBDIR := $(PREFIX)/lib
endif
ifeq ($(PLUGINDIR),)
  PLUGINDIR := $(LIBDIR)/mupen64plus
endif

SRCDIR = ../../src
OBJDIR = _obj$(POSTFIX)

SOURCE = \
    $(SRCDIR)/2xSAI.cpp \
    $(SRCDIR)/Combiner.cpp \
    $(SRCDIR)/CRC.cpp \
    $(SRCDIR)/DepthBuffer.cpp \
    $(SRCDIR)/F3D.cpp \
    $(SRCDIR)/F3DDKR.cpp \
    $(SRCDIR)/F3DEX.cpp \
    $(SRCDIR)/F3DEX2.cpp \
    $(SRCDIR)/F3DPD.cpp \
    $(SRCDIR)/F3DWRUS.cpp \
    $(SRCDIR)/FrameBuffer.cpp \
    $(SRCDIR)/GBI.cpp \
    $(SRCDIR)/gDP.cpp \
    $(SRCDIR)/glN64.cpp \
    $(SRCDIR)/gSP.cpp \
    $(SRCDIR)/L3D.cpp \
    $(SRCDIR)/L3DEX.cpp \
    $(SRCDIR)/L3DEX2.cpp \
    $(SRCDIR)/N64.cpp \
    $(SRCDIR)/RDP.cpp \
    $(SRCDIR)/RSP.cpp \
    $(SRCDIR)/S2DEX.cpp \
    $(SRCDIR)/S2DEX2.cpp \
    $(SRCDIR)/Textures.cpp \
    $(SRCDIR)/VCAtlas.cpp \
    $(SRCDIR)/VCCombiner.cpp \
    $(SRCDIR)/VCConfig.cpp \
    $(SRCDIR)/VCDebugger.cpp \
    $(SRCDIR)/VCRenderer.cpp \
    $(SRCDIR)/VCUtils.cpp \
    $(SRCDIR)/VI.cpp

SOURCE += $(SRCDIR)/xxhash.c

SHADERS = \
    $(SRCDIR)/blit.fs.glsl \
    $(SRCDIR)/blit.vs.glsl \
    $(SRCDIR)/debug.fs.glsl \
    $(SRCDIR)/debug.vs.glsl \
    $(SRCDIR)/n64.fs.glsl \
    $(SRCDIR)/n64.vs.glsl

# generate a list of object files build, make a temporary directory for them
OBJECTS := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(filter %.c, $(SOURCE)))
OBJECTS += $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(filter %.cpp, $(SOURCE)))
OBJDIRS = $(dir $(OBJECTS))
$(shell $(MKDIR) $(OBJDIRS))

# build targets
TARGET = mupen64plus-video-videocore$(POSTFIX).$(SO_EXTENSION)

targets:
	@echo "Mupen64plus-video-videocore N64 Graphics plugin makefile. "
	@echo "  Targets:"
	@echo "    all           == Build Mupen64plus-video-rice plugin"
	@echo "    clean         == remove object files"
	@echo "    rebuild       == clean and re-build all"
	@echo "    install       == Install Mupen64Plus-video-rice plugin"
	@echo "    uninstall     == Uninstall Mupen64Plus-video-rice plugin"
	@echo "  Install Options:"
	@echo "    PREFIX=path   == install/uninstall prefix (default: /usr/local)"
	@echo "    SHAREDIR=path == path to install shared data files (default: PREFIX/share/mupen64plus)"
	@echo "    LIBDIR=path   == library prefix (default: PREFIX/lib)"
	@echo "    PLUGINDIR=path == path to install plugin libraries (default: LIBDIR/mupen64plus)"
	@echo "    DESTDIR=path  == path to prepend to all installation paths (only for packagers)"

all: $(TARGET)

install: $(TARGET)
	$(INSTALL) -d "$(DESTDIR)$(PLUGINDIR)"
	$(INSTALL) -m 0644 $(INSTALL_STRIP_FLAG) $(TARGET) "$(DESTDIR)$(PLUGINDIR)"
	$(INSTALL) -d "$(DESTDIR)$(SHAREDIR)"
	$(INSTALL) -m 0644 "../../data/videocore.conf" "$(DESTDIR)$(SHAREDIR)"
	$(INSTALL) -m 0644 "$(SRCDIR)/blit.fs.glsl" "/usr/local/share/mupen64plus/videocore/"
	$(INSTALL) -m 0644 "$(SRCDIR)/blit.vs.glsl" "/usr/local/share/mupen64plus/videocore/"
	$(INSTALL) -m 0644 "$(SRCDIR)/debug.fs.glsl" "/usr/local/share/mupen64plus/videocore/"
	$(INSTALL) -m 0644 "$(SRCDIR)/debug.vs.glsl" "/usr/local/share/mupen64plus/videocore/"
	$(INSTALL) -m 0644 "$(SRCDIR)/n64.fs.glsl" "/usr/local/share/mupen64plus/videocore/"
	$(INSTALL) -m 0644 "$(SRCDIR)/n64.vs.glsl" "/usr/local/share/mupen64plus/videocore/"

uninstall:
	$(RM) "$(DESTDIR)$(PLUGINDIR)/$(TARGET)"
	$(RM) "$(DESTDIR)$(SHAREDIR)/videocore.conf"

clean:
	$(RM) -r $(OBJDIR) $(TARGET)

rebuild: clean all

# build dependency files
CFLAGS += -MD -MP
-include $(OBJECTS:.o=.d)

CXXFLAGS += $(CFLAGS)

# standard build rules
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(COMPILE.c) -o $@ $<

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(COMPILE.cc) -o $@ $<

$(TARGET): $(OBJECTS)
	$(LINK.o) $^ $(LOADLIBES) $(LDLIBS) -o $@

.PHONY: all clean install uninstall targets