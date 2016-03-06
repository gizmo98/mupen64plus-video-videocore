// mupen64plus-video-videocore/VCAtlas.h
//
// Copyright (c) 2016 The mupen64plus-video-videocore Authors

#ifndef VC_ATLAS_H
#define VC_ATLAS_H

#include <stdlib.h>
#include "VCGL.h"
#include "VCGeometry.h"
#include "uthash.h"
#include "xxhash.h"

#define VC_ATLAS_TEXTURE_SIZE   1024

struct VCN64Vertex;
struct VCRenderCommand;
struct VCRenderer;
struct gDPTile;

struct VCTextureInfo {
    VCRectus uv;
    bool repeatX;
    bool repeatY;
    bool mirrorX;
    bool mirrorY;
};

struct VCCachedTexture {
    VCTextureInfo info;
    bool valid;
};

struct VCUploadedTexture {
    VCTextureInfo info;
    XXH32_hash_t tmemHash;
    UT_hash_handle hh;
};

struct VCAtlas {
    GLuint texture;
    VCTextureInfo textureInfo[8];
    bool textureInfoValid[8];
    VCUploadedTexture *uploadedTextures;
    VCRectus *freeList;
    size_t freeListSize;
    size_t freeListCapacity;
    XXH32_state_t *hashState;
};

void VCAtlas_Create(VCAtlas *atlas);
bool VCAtlas_Allocate(VCAtlas *atlas, VCRectus *result, VCSize2us *size);
void VCAtlas_Bind(VCAtlas *atlas);
GLint VCAtlas_GetGLTexture(VCAtlas *atlas);
void VCAtlas_FillTextureBounds(VCRects *textureBounds, VCTextureInfo *textureInfo);
void VCAtlas_ProcessUploadCommand(VCAtlas *atlas, VCRenderCommand *command);
void VCAtlas_GetOrUploadTexture(VCAtlas *atlas,
                                VCRenderer *renderer,
                                VCTextureInfo *textureInfo,
                                gDPTile *tile);
void VCAtlas_InvalidateCache(VCAtlas *atlas);

#endif

