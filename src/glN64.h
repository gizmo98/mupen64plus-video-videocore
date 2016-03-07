#ifndef GLN64_H
#define GLN64_H

#include "m64p_config.h"
#include "stdio.h"
#include "m64p_vidext.h"

//#define DEBUG
//#define RSPTHREAD

#define PLUGIN_NAME     "videocore"
#define PLUGIN_VERSION  0x000005
#define PLUGIN_API_VERSION 0x020200

extern char pluginName[];

extern void (*CheckInterrupts)( void );
extern char *screenDirectory;

extern ptr_ConfigGetSharedDataFilepath  ConfigGetSharedDataFilepath;
extern ptr_ConfigGetUserConfigPath      ConfigGetUserConfigPath;
extern ptr_VidExt_GL_SwapBuffers        CoreVideo_GL_SwapBuffers;
extern ptr_VidExt_SetVideoMode          CoreVideo_SetVideoMode;
extern ptr_VidExt_GL_SetAttribute       CoreVideo_GL_SetAttribute;
extern ptr_VidExt_GL_GetAttribute       CoreVideo_GL_GetAttribute;
extern ptr_VidExt_Init                  CoreVideo_Init;
extern ptr_VidExt_Quit                  CoreVideo_Quit;

extern void (*CheckInterrupts)( void );
extern void (*renderCallback)();

#endif

