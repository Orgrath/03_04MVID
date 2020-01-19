#include <glad/glad.h>

#include "engine/input.hpp"
#include "engine/window.hpp"
#include "engine/shader.hpp"

#include <iostream>
#include <GLFW\glfw3.h>

void handleInput() {
    std::vector<std::pair<int, int>> keys = Input::instance()->getKeys();
    for (auto& key : keys) {
        std::cout << key.first << " - " << key.second << std::endl;
    }
}

uint32_t createVertexData(uint32_t* VBO, uint32_t* EBO) {
    float vertices[] = {
        0.5f, -0.5f, 0.0f,      0.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 0.0f,
        0.0f, 0.5f, 0.0f,       0.0f, 0.0f, 0.0f
    };

    uint32_t indices[] = {
        0, 2, 1
    };

    uint32_t VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, VBO);
    glGenBuffers(1, EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return VAO;
}


void render(uint32_t VAO, const Shader& shader, float modColor[]){

    glClear(GL_COLOR_BUFFER_BIT);

    shader.use();
    //std::cout << "Rojo: " << modColor[0] << "Verde: " << modColor[1] << "Azul: " << modColor[2] << std::endl;
    shader.set("addColor", modColor[0], modColor[1], modColor[2]);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

int main(int, char* []) {
    Window* window = Window::instance();

    glClearColor(0.0f, 0.3f, 0.6f, 1.0f);

    uint32_t VBO, EBO;
    const uint32_t VAO = createVertexData(&VBO, &EBO);
    const Shader shader("../projects/EJ03_02/vertex.vs", "../projects/EJ03_02/fragment.fs");
    float modColor[3];
    float timeValue;
    float colorValue;
    int tick[] = { 1, 0, 0 };//empezamos con rojo

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    while (window->alive()) {
        handleInput();
        timeValue = glfwGetTime()/2;
        colorValue = fabs(sin(timeValue));
        //std::cout << colorValue << std::endl;
        if (tick[0] > 0 && colorValue >= 0.0f && colorValue <= 1.0f) {
            if (colorValue > 0.9999f) { tick[0] = 2; /*std::cout << "Rojo llego a 1 - tick: " << tick[0] << std::endl;*/ }
            if (colorValue <= 0.01f && tick[0] == 2) { tick[0] = 0; tick[1] = 1; /*std::cout << "Rojo llego a 0 - tick: " << tick[0] << std::endl;*/ }
            modColor[0] = colorValue;
        }
        if (tick[1] > 0 && colorValue >= 0.0f && colorValue <= 1.0f) {
            if (colorValue > 0.9999f) { tick[1] = 2; /*std::cout << "Verde llego a 1" << std::endl;*/}
            if (colorValue <= 0.01f && tick[1] == 2) { tick[1] = 0; tick[2] = 1; /*std::cout << "Verde llego a 0" << std::endl;*/}
            modColor[1] = colorValue;
        }
        if (tick[2] > 0 && colorValue >= 0.0f && colorValue <= 1.0f) {
            if (colorValue > 0.9999f) { tick[2] = 2; /*std::cout << "Azul llego a 1" << std::endl;*/}
            if (colorValue <= 0.01f && tick[2] == 2) { tick[2] = 0; tick[0] = 1; /*std::cout << "Azul llego a 0" << std::endl;*/}
            modColor[2] = colorValue;
        }
        render(VAO, shader, modColor);
        window->frame();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    return 0;
}