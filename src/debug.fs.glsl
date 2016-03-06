// mupen64plus-video-videocore/debug.fs.glsl

uniform sampler2D uTexture;

varying vec4 vColor;
varying vec2 vTextureUv;

void main(void) {
    gl_FragColor = texture2D(uTexture, vTextureUv) * vColor;
}

