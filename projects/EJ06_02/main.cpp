#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "engine/camera.hpp"
#include "engine/geometry/cube.hpp"
#include "engine/geometry/quad.hpp"
#include "engine/input.hpp"
#include "engine/shader.hpp"
#include "engine/texture.hpp"
#include "engine/window.hpp"
#include "engine/geometry/sphere.hpp"

#include <iostream>

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastFrame = 0.0f;
float lastX, lastY;
bool firstMouse = true;

void handleInput(float dt) {
    Input* input = Input::instance();

    if (input->isKeyPressed(GLFW_KEY_W)) {
        camera.handleKeyboard_EJ06_01(Camera::Movement::Forward, dt);
    }
    if (input->isKeyPressed(GLFW_KEY_S)) {
        camera.handleKeyboard_EJ06_01(Camera::Movement::Backward, dt);
    }
    if (input->isKeyPressed(GLFW_KEY_A)) {
        camera.handleKeyboard(Camera::Movement::Left, dt);
    }
    if (input->isKeyPressed(GLFW_KEY_D)) {
        camera.handleKeyboard(Camera::Movement::Right, dt);
    }
}

void onKeyPress(int key, int action) {
    if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
        Window::instance()->setCaptureMode(true);
    }

    if (key == GLFW_KEY_E && action == GLFW_PRESS) {
        Window::instance()->setCaptureMode(false);
    }
}

void onMouseMoved(float x, float y) {
    if (firstMouse) {
        firstMouse = false;
        lastX = x;
        lastY = y;
    }

    const float xoffset = x - lastX;
    const float yoffset = lastY - y;
    lastX = x;
    lastY = y;

    camera.handleMouseMovement(xoffset, yoffset);
}

void onScrollMoved(float x, float y) {
    camera.handleMouseScroll(y);
}

void render(const Geometry& geom1, const Geometry& geom2, const Shader& shader, Texture& tex1, Texture& tex2) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDepthFunc(GL_LESS);

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -1.0f));

    glm::mat4 proj = glm::perspective(glm::radians(camera.getFOV()), 800.0f / 600.0f, 0.1f, 100.0f);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(2.25f, 2.0f, 1.0f));
    model = glm::translate(model, glm::vec3(0.0f, -0.25f, 0.0f));
    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(-1.0f, 0.0f, 0.0f));

    glm::vec3 cubePositions[] = {
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(0.5f, 0.5f, 0.5f),
        glm::vec3(0.0f, 0.1f, 0.0f),
        glm::vec3(-0.5f, 0.5f, -0.5f),
        glm::vec3(-1.0f, 1.0f, -1.0f),
    };

    glm::vec3 cubeScales[] = {
        glm::vec3(1.0f, 2.0f, 1.25f),
        glm::vec3(0.5f, 1.0f, 0.75f),
        glm::vec3(3.0f, 1.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(1.25f, 1.25f, 1.25f),
    };

    tex2.use(shader, "tex", 0);
    shader.set("model", model);
    geom2.render();

    shader.use();
    shader.set("view", camera.getViewMatrix_EJ06_02());
    shader.set("proj", proj);  //TODO const mat4

    tex1.use(shader, "tex", 0);

    for (uint8_t i = 0; i < 5; i++) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);
        model = glm::scale(model, cubeScales[i]);
        shader.set("model", model);

        geom1.render();
    }

}

void render(const Geometry& geom, const Shader& shader, Texture& tex) {
    glClear(GL_COLOR_BUFFER_BIT);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, static_cast<float>(glfwGetTime())* glm::radians(20.0f), glm::vec3(0.5f, 1.0f, 0.0f));

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    glm::mat4 proj = glm::perspective(glm::radians(camera.getFOV()), 800.0f / 600.0f, 0.1f, 100.0f);

    shader.use();

    tex.use(shader, "tex", 0);

    shader.set("model", model);
    shader.set("view", camera.getViewMatrix());
    shader.set("proj", proj);  //TODO const mat4

    geom.render();

}

int main(int, char* []) {
    Window* window = Window::instance();

    glClearColor(0.0f, 0.3f, 0.6f, 1.0f);

    const Shader shader("../projects/EJ06_01/vertex.vs", "../projects/EJ06_01/fragment.fs");
    const Cube cube(0.2f);
    const Quad quad(3.0f);

    Texture tex("../assets/textures/blue_blocks.jpg", Texture::Format::RGB);
    Texture tex1("../assets/textures/bricks_arrow.jpg", Texture::Format::RGB);

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glCullFace(GL_BACK);

    Input::instance()->setKeyPressedCallback(onKeyPress);
    Input::instance()->setMouseMoveCallback(onMouseMoved);
    Input::instance()->setScrollMoveCallback(onScrollMoved);

    while (window->alive()) {
        const float currentFrame = glfwGetTime();
        const float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        handleInput(deltaTime);
        render(cube, quad, shader, tex, tex1);
        window->frame();
    }

    return 0;
}