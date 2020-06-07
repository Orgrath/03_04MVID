#version 330 core

out vec4 FragColor;

in vec2 uv;

uniform sampler2D screenTexture;
uniform bool horizontal;

const float offset = 1.0 / 600.0;

void main() {
    vec2 offsets[9] = vec2[](
        vec2(-offset, offset),
        vec2(0.0, offset),
        vec2(offset, offset),
        vec2(-offset, 0.0),
        vec2(0.0, 0.0),
        vec2(offset, 0.0),
        vec2(-offset, -offset),
        vec2(0.0, -offset),
        vec2(offset, -offset)
    );

    float kernel[4] = float[] (
        0.22508352, 0.11098164, 0.01330373, 0.00038771
    );

    vec2 tex_offset = 1.0 / textureSize(screenTexture, 0);
    vec3 color = vec3(texture(screenTexture, uv.st))* kernel[0];

    if (horizontal){
        for (int i = 0; i < 4; ++i) {
            color += vec3(texture(screenTexture, uv.st + vec2(tex_offset.x * i))) * kernel[i];
            color += vec3(texture(screenTexture, uv.st - vec2(tex_offset.x * i))) * kernel[i];
        }
    }
    else{
        for (int i = 0; i < 4; ++i) {
            color += vec3(texture(screenTexture, uv.st + vec2(tex_offset.y * i))) * kernel[i];
            color += vec3(texture(screenTexture, uv.st - vec2(tex_offset.y * i))) * kernel[i];
        }
    }

    FragColor = vec4(color, 1.0);
}