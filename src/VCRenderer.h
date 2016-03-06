// mupen64plus-video-videocore/VCRenderer.h
//
// Copyright (c) 2016 The mupen64plus-video-videocore Authors

#ifndef VCRENDERER_H
#define VCRENDERER_H

#define VC_N64_WIDTH 320
#define VC_N64_HEIGHT 240

#define VC_RENDER_COMMAND_NONE              0
#define VC_RENDER_COMMAND_UPLOAD_TEXTURE    1
#define VC_RENDER_COMMAND_DRAW_BATCHES      2

#define VC_TRIANGLE_MODE_NORMAL             0
#define VC_TRIANGLE_MODE_TEXTURE_RECTANGLE  1
#define VC_TRIANGLE_MODE_RECT_FILL          2

#include <SDL2/SDL.h>
#include <stdint.h>
#include "VCAtlas.h"
#include "VCDebugger.h"
#include "VCGeometry.h"

struct Combiner;
struct SPVertex;

struct VCBlendFlags {
    bool zTest;
    bool zUpdate;
    bool cullFront;
    bool cullBack;
    VCRectf viewport;
};

struct VCCombiner {
    VCColorf combineA;
    VCColorf combineB;
    VCColorf combineC;
    VCColorf combineD;
};

struct VCN64Vertex {
    VCPoint4f position;
    VCPoint2f textureUV;
    VCRects texture0Bounds;
    VCRects texture1Bounds;
    VCCombiner combiner;
};

struct VCBlitVertex {
    VCPoint2f position;
    VCPoint2f textureUV;
};

struct VCBatch {
    VCN64Vertex *vertices;
    size_t verticesLength;
    size_t verticesCapacity;
    VCBlendFlags blendFlags;
};

struct VCRenderCommand {
    uint8_t command;
    VCRectus uv;
    uint8_t *pixels;
    uint32_t elapsedTime;
};

struct VCRenderer {
    SDL_Window *window;
    SDL_GLContext context;

    bool ready;
    SDL_mutex *readyMutex;
    SDL_cond *readyCond;

    VCSize2u windowSize;

    VCRenderCommand *commands;
    size_t commandsLength;
    size_t commandsCapacity;

    bool commandsQueued;
    SDL_mutex *commandsMutex;
    SDL_cond *commandsCond;

    VCBatch *batches;
    size_t batchesLength;
    size_t batchesCapacity;

    VCAtlas atlas;
    VCDebugger *debugger;

    VCProgram n64Program;
    VCProgram blitProgram;

    GLuint fbo;
    GLuint fboTexture;
    GLuint depthRenderbuffer;
};

VCRenderer *VCRenderer_SharedRenderer();
void VCRenderer_Start(VCRenderer *renderer);
void VCRenderer_CreateProgram(GLuint *program, GLuint vertexShader, GLuint fragmentShader);
void VCRenderer_CompileShader(GLuint *shader, GLint shaderType, const char *path);
void VCRenderer_AddVertex(VCRenderer *renderer, VCN64Vertex *vertex, VCBlendFlags *blendFlags);
void VCRenderer_EnqueueCommand(VCRenderer *renderer, VCRenderCommand *command);
void VCRenderer_SubmitCommands(VCRenderer *renderer);
void VCRenderer_InitColorCombinerForFill(VCN64Vertex *vertex);
void VCRenderer_InitColorCombinerForTextureBlit(VCN64Vertex *vertex);
void VCRenderer_InitTriangleVertices(VCRenderer *renderer,
                                     VCN64Vertex *n64Vertices,
                                     SPVertex *spVertices,
                                     uint32_t *indices,
                                     uint32_t indexCount,
                                     uint8_t mode);
VCCombiner *VCRenderer_CompileCombiner(Combiner *color, Combiner *alpha);

#endif

