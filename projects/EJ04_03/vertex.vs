#version 330 core

layout (location=0) in vec3 aPos;
layout (location=1) in vec3 aColor;
layout (location=2) in vec2 aUV;

out vec2 UV;
uniform float addMult;

void main() {
    //UV = aUV;
    UV = aUV * addMult;
    gl_Position = vec4(aPos, 1.0);
}