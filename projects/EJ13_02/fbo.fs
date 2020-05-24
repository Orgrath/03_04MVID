#version 330 core

out vec4 FragColor;

in vec2 uv;

uniform sampler2D screenTexture;

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

    float Gx[9] = float[] (
        -1, 0, 1,
        -2, 0, 2,
        -1, 0, 1
    );
    float Gy[9] = float[] (
        1, 2, 1,
        0, 0, 0,
        -1, -2, -1
    );

    vec3 color = vec3(texture(screenTexture, uv.st));
    //mat3 I;
    float I[9] = float[] (
        0, 0, 0,
        0, 0, 0,
        0, 0, 0
    );
    float Sx = 0.0;
    float Sy = 0.0;

    for (int i = 0; i < 9; ++i) {
        vec3 sample = vec3(texture(screenTexture, uv.st + offsets[i]));
        I[i] = length(sample);
        Sx += dot(Gx[i], I[i]);
        Sy += dot(Gy[i], I[i]);
    }

    float Mag = sqrt(pow(Sx, 2.0) + pow(Sy, 2.0));

    if (Mag < 0.7){
        color = vec3(1.0, 1.0, 1.0);
    }
    else{
        color = vec3(0.0, 0.0, 0.0);   
    }

    FragColor = vec4(color, 1.0);
}
