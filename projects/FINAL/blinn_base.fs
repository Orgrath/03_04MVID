#version 330 core

out vec4 FragColor;

struct Base {
    vec3 color;
    float transparency;
};
uniform Base base;

void main() {
    FragColor = vec4(base.color, base.transparency);
}