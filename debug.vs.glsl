// mupen64plus-video-videocore/debug.vs.glsl

attribute vec2 aPosition;
attribute vec4 aColor;
attribute vec2 aTextureUv;

varying vec4 vColor;
varying vec2 vTextureUv;

void main(void) {
    vColor = aColor;
    vTextureUv = aTextureUv;
    gl_Position = vec4(aPosition, 0.0, 1.0);
}

