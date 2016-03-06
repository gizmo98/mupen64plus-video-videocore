// mupen64plus-video-videocore/n64.fs.glsl

uniform sampler2D uTexture0;
uniform sampler2D uTexture1;

varying vec2 vTextureUv;
varying vec4 vTexture0Bounds;
varying vec4 vTexture1Bounds;
varying vec4 vCombineA;
varying vec4 vCombineB;
varying vec4 vCombineC;
varying vec4 vCombineD;

vec3 CombineColor(vec3 combiner, vec4 texel0, vec4 texel1) {
    if (combiner.r >= 0.0)
        return combiner;
    if (combiner.g < 0.0) {
        if (combiner.b < 0.0)
            return texel0.aaa;
        return texel1.aaa;
    }
    if (combiner.b < 0.0)
        return texel0.rgb;
    return texel1.rgb;
}

float CombineAlpha(float combiner, float texel0, float texel1) {
    if (combiner < 0.0)
        return (combiner < -100.0) ? texel0 : texel1;
    return combiner;
}

vec2 AtlasUv(vec4 textureBounds) {
    vec2 uv = vTextureUv;
    if (textureBounds.z > 0.0)
        uv.x = clamp(uv.x, 0.0, 1.0);
    else if (uv.x < 0.0)
        uv.x = 1.0 - fract(uv.x);
    else
        uv.x = fract(uv.x);

    if (textureBounds.w > 0.0)
        uv.y = clamp(uv.y, 0.0, 1.0);
    else if (uv.y < 0.0)
        uv.y = 1.0 - fract(uv.y);
    else
        uv.y = fract(uv.y);

    return uv * abs(textureBounds.zw) + textureBounds.xy;
}

void main(void) {
    vec4 texture0Color = texture2D(uTexture0, AtlasUv(vTexture0Bounds));
    vec4 texture1Color = texture2D(uTexture1, AtlasUv(vTexture1Bounds));
    vec4 color = vec4(CombineColor(vCombineA.rgb, texture0Color, texture1Color),
                      CombineAlpha(vCombineA.a, texture0Color.a, texture1Color.a));
    color -= vec4(CombineColor(vCombineB.rgb, texture0Color, texture1Color),
                  CombineAlpha(vCombineB.a, texture0Color.a, texture1Color.a));
    color *= vec4(CombineColor(vCombineC.rgb, texture0Color, texture1Color),
                  CombineAlpha(vCombineC.a, texture0Color.a, texture1Color.a));
    color += vec4(CombineColor(vCombineD.rgb, texture0Color, texture1Color),
                  CombineAlpha(vCombineD.a, texture0Color.a, texture1Color.a));
    if (color.a == 0.0)
        discard;
    gl_FragColor = color;
}

