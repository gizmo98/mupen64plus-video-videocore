// mupen64plus-video-videocore/n64.vs.glsl

attribute vec4 aPosition;
attribute vec2 aTextureUv;
attribute vec4 aTexture0Bounds;
attribute vec4 aTexture1Bounds;
attribute vec4 aCombineA;
attribute vec4 aCombineB;
attribute vec4 aCombineC;
attribute vec4 aCombineD;

varying vec2 vTextureUv;
varying vec4 vTexture0Bounds;
varying vec4 vTexture1Bounds;
varying vec4 vCombineA;
varying vec4 vCombineB;
varying vec4 vCombineC;
varying vec4 vCombineD;

void main(void) {
    if (aTexture0Bounds.z != 0.0 && aTexture0Bounds.w != 0.0)
        vTextureUv = aTextureUv / abs(aTexture0Bounds.zw);  // FIXME(tachi)
    else
        vTextureUv = aTextureUv;
    vTexture0Bounds = aTexture0Bounds / 1024.0;
    vTexture1Bounds = aTexture1Bounds / 1024.0;
    vCombineA = aCombineA;
    vCombineB = aCombineB;
    vCombineC = aCombineC;
    vCombineD = aCombineD;
    gl_Position = aPosition;
}

