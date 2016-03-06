// mupen64plus-video-videocore/blit.vs.glsl

attribute vec2 aPosition;
attribute vec2 aTextureUv;

varying vec2 vTextureUv;

void main(void) {
    vTextureUv = aTextureUv;
    gl_Position = vec4(aPosition, 0.0, 1.0);
}

