#version 330 core

out vec4 fragColor;

in vec2 textureCoord;

uniform float colorBlend;
uniform vec4 color;
uniform sampler2D particleTexture;

void main() {
    vec4 tex = texture(particleTexture, textureCoord);
    if (tex.a <= 0.0)
        discard;

    fragColor = mix(color, vec4(tex.r, tex.g, tex.b, color.a), colorBlend);
}
