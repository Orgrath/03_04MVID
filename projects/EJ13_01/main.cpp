#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "engine/camera.hpp"
#include "engine/geometry/cube.hpp"
#include "engine/input.hpp"
#include "engine/shader.hpp"
#include "engine/texture.hpp"
#include "engine/window.hpp"
#include "engine/renderfbo.hpp"
#include "engine/geometry/sphere.hpp"
#include "engine/geometry/quad.hpp"
#include "engine/geometry/teapot.hpp"
#include <iostream>

const float velocity = 0.005f;

Camera cameraP(glm::vec3(0.0f, 1.0f, 10.0f));
Camera cameraV(glm::vec3(-4.5f, 1.4f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), -8.0f, -5.0f);
int32_t resolutionWidth;
int32_t resolutionHeight;

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

glm::vec3 cubePositions[] = {
    glm::vec3(4.0f, 0.0f, 0.0f),
    glm::vec3(-4.0f, 0.0f, 0.0f),
    glm::vec3(0.0f, 0.0f, 4.0f),
    glm::vec3(0.0f, 0.0f, -4.0f),
    glm::vec3(4.0f, 0.0f, 4.0f),
    glm::vec3(4.0f, 0.0f, -4.0f),
    glm::vec3(-4.0f, 0.0f, 4.0f),
    glm::vec3(-4.0f, 0.0f, -4.0f),
};

float lastFrame = 0.0f;
float lastX, lastY;
bool firstMouse = true;

void handleInput(float dt) {
    Input* input = Input::instance();

    if (input->isKeyPressed(GLFW_KEY_W)) {
        cameraP.handleKeyboard(Camera::Movement::Forward, dt + velocity);
    }
    if (input->isKeyPressed(GLFW_KEY_S)) {
        cameraP.handleKeyboard(Camera::Movement::Backward, dt + velocity);
    }
    if (input->isKeyPressed(GLFW_KEY_A)) {
        cameraP.handleKeyboard(Camera::Movement::Left, dt + velocity);
    }
    if (input->isKeyPressed(GLFW_KEY_D)) {
        cameraP.handleKeyboard(Camera::Movement::Right, dt + velocity);
    }
    if (input->isKeyPressed(GLFW_KEY_SPACE)) {
        cameraP.handleKeyboard(Camera::Movement::Up, dt + velocity);
    }
    if (input->isKeyPressed(GLFW_KEY_LEFT_CONTROL)) {
        cameraP.handleKeyboard(Camera::Movement::Down, dt + velocity);
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

    cameraP.handleMouseMovement(xoffset, yoffset);
}

void onScrollMoved(float x, float y) {
    cameraP.handleMouseScroll(y);
}

void render(const Geometry& quad, const Geometry& cube, const Geometry& teapot, const Geometry& visor, const Shader& s_phong, const Shader& s_fbo,
    const Texture& t_albedo, const Texture& t_specular, const uint32_t fbo, const uint32_t fbo_texture) {

    //FIRST PASS
    glm::mat4 view = cameraV.getViewMatrix();
    glm::mat4 proj = glm::perspective(glm::radians(cameraV.getFOV()), static_cast<float>(resolutionWidth) / resolutionHeight, 0.1f, 100.0f);

    float moveCamV = cos(glfwGetTime()/2.0f);
    cameraV.handleMouseMovement(moveCamV, 0.0f);

    glEnable(GL_DEPTH_TEST);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    s_phong.use();
    s_phong.set("view", view);
    s_phong.set("proj", proj);

    s_phong.set("viewPos", cameraV.getPosition());

    s_phong.set("light.position", lightPos);
    s_phong.set("light.ambient", 0.1f, 0.1f, 0.1f);
    s_phong.set("light.diffuse", 0.5f, 0.5f, 0.5f);
    s_phong.set("light.specular", 1.0f, 1.0f, 1.0f);

    t_albedo.use(s_phong, "material.diffuse", 0);
    t_specular.use(s_phong, "material.specular", 1);
    s_phong.set("material.shininess", 32);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
    model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    s_phong.set("model", model);
    glm::mat3 normalMat = glm::inverse(glm::transpose(glm::mat3(model)));
    s_phong.set("normalMat", normalMat);

    quad.render();

    model = glm::mat4(1.0f);
    s_phong.set("model", model);
    normalMat = glm::inverse(glm::transpose(glm::mat3(model)));
    s_phong.set("normalMat", normalMat);

    cube.render();

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.0f));
    model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
    s_phong.set("model", model);
    normalMat = glm::inverse(glm::transpose(glm::mat3(model)));
    s_phong.set("normalMat", normalMat);

    teapot.render();

    for (const auto& cubePos : cubePositions) {
        model = glm::mat4(1.0f);
        model = glm::translate(model, cubePos);
        s_phong.set("model", model);

        glm::mat3 normalMat = glm::inverse(glm::transpose(glm::mat3(model)));
        s_phong.set("normalMat", normalMat);

        cube.render();
    }


    
    //SECOND PASS
    view = cameraP.getViewMatrix();
    proj = glm::perspective(glm::radians(cameraP.getFOV()), static_cast<float>(resolutionWidth) / resolutionHeight, 0.1f, 100.0f);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    s_phong.use();
    s_phong.set("view", view);
    s_phong.set("proj", proj);

    //s_phong.set("viewPos", cameraV.getPosition());
    s_phong.set("viewPos", cameraP.getPosition());

    s_phong.set("light.position", lightPos);
    s_phong.set("light.ambient", 0.1f, 0.1f, 0.1f);
    s_phong.set("light.diffuse", 0.5f, 0.5f, 0.5f);
    s_phong.set("light.specular", 1.0f, 1.0f, 1.0f);

    t_albedo.use(s_phong, "material.diffuse", 0);
    t_specular.use(s_phong, "material.specular", 1);
    s_phong.set("material.shininess", 32);

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
    model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    s_phong.set("model", model);
    normalMat = glm::inverse(glm::transpose(glm::mat3(model)));
    s_phong.set("normalMat", normalMat);

    quad.render();

    model = glm::mat4(1.0f);
    s_phong.set("model", model);
    normalMat = glm::inverse(glm::transpose(glm::mat3(model)));
    s_phong.set("normalMat", normalMat);

    cube.render();

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.0f));
    model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
    s_phong.set("model", model);
    normalMat = glm::inverse(glm::transpose(glm::mat3(model)));
    s_phong.set("normalMat", normalMat);

    teapot.render();

    for (const auto& cubePos : cubePositions) {
        model = glm::mat4(1.0f);
        model = glm::translate(model, cubePos);
        s_phong.set("model", model);

        glm::mat3 normalMat = glm::inverse(glm::transpose(glm::mat3(model)));
        s_phong.set("normalMat", normalMat);

        cube.render();
    }

    s_fbo.use();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, fbo_texture);
    s_fbo.set("screenTexture", 0);

    visor.render();

}

int main(int, char* []) {
    Window* window = Window::instance();
    window->setWidth(1024);
    window->setHeight(768);

    resolutionWidth = Window::instance()->getWidth();
    resolutionHeight = Window::instance()->getHeight();

    glClearColor(0.0f, 0.0f, 0.6f, 1.0f);

    const Shader s_phong("../projects/EJ13_01/phong.vs", "../projects/EJ13_01/blinn.fs");
    const Shader s_fbo("../projects/EJ13_01/fbo.vs", "../projects/EJ13_01/fbo.fs");
    const Texture t_albedo("../assets/textures/bricks_albedo.png", Texture::Format::RGB);
    const Texture t_specular("../assets/textures/bricks_specular.png", Texture::Format::RGB);
    const Quad quad(10.0f);
    const Quad visor(0.75f, 4);
    const Cube cube(1.0f);
    const Teapot teapot(1);
    const float cameraDirH = 0.0f;
    const float cameraDirW = 0.5f;

    RenderFBO renderfbo(resolutionWidth, resolutionHeight);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    Input::instance()->setKeyPressedCallback(onKeyPress);
    Input::instance()->setMouseMoveCallback(onMouseMoved);
    Input::instance()->setScrollMoveCallback(onScrollMoved);

    while (window->alive()) {
        const float currentFrame = glfwGetTime();
        const float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        handleInput(deltaTime);

        render(quad, cube, teapot, visor, s_phong, s_fbo, t_albedo, t_specular, renderfbo.getFBO(), renderfbo.getTextureColor());

        window->frame();
    }

    renderfbo.DeleteFBO();

    return 0;
}