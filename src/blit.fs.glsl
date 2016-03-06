// mupen64plus-video-videocore/blit.fs.glsl

uniform sampler2D uTexture;

varying vec2 vTextureUv;

void main(void) {
    gl_FragColor = texture2D(uTexture, vTextureUv);
}

