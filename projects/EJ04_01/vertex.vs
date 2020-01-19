#version 330 core

layout (location=0) in vec3 aPos;
layout (location=1) in vec3 aColor;
layout (location=2) in vec2 aUV;

out vec2 UV;
out vec2 myColor;

void main() {
    UV = aUV;
    myColor = vec2(aColor.x,aColor.y);
    gl_Position = vec4(aPos, 1.0);
}