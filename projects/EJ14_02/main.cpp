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
#include <iostream>

const float velocity = 0.005f;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
glm::vec3 spotLightPos[] = {
    glm::vec3(-2.0f, 3.0f, 2.5f),
    glm::vec3(3.0f, 4.0f, 0.0f)
};
glm::vec3 spotlightDirs[] = {
    glm::vec3(2.0f, -2.0f,-2.0f),
    glm::vec3(-3.0f, -3.0f, 0.0f)
};

const uint32_t k_shadow_height = 1024;
const uint32_t k_shadow_width = 1024;
const float k_shadow_near = 1.0f;
const float k_shadow_far = 14.0f;

float lastFrame = 0.0f;
float lastX, lastY;
bool firstMouse = true;

void handleInput(float dt) {
    Input* input = Input::instance();

    if (input->isKeyPressed(GLFW_KEY_W)) {
        camera.handleKeyboard(Camera::Movement::Forward, dt + velocity);
    }
    if (input->isKeyPressed(GLFW_KEY_S)) {
        camera.handleKeyboard(Camera::Movement::Backward, dt + velocity);
    }
    if (input->isKeyPressed(GLFW_KEY_A)) {
        camera.handleKeyboard(Camera::Movement::Left, dt + velocity);
    }
    if (input->isKeyPressed(GLFW_KEY_D)) {
        camera.handleKeyboard(Camera::Movement::Right, dt + velocity);
    }
    if (input->isKeyPressed(GLFW_KEY_SPACE)) {
        camera.handleKeyboard(Camera::Movement::Up, dt + velocity);
    }
    if (input->isKeyPressed(GLFW_KEY_LEFT_CONTROL)) {
        camera.handleKeyboard(Camera::Movement::Down, dt + velocity);
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

void renderScene(const Shader& shader, 
    const Geometry& quad, const Geometry& cube, const Geometry& sphere, const Geometry& light,
    const Texture& t_albedo, const Texture& t_specular) {
    
    //shader.use();
    t_albedo.use(shader, "material.diffuse", 0);
    t_specular.use(shader, "material.specular", 1);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
    model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
    shader.set("model", model);
    glm::mat3 normalMat = glm::inverse(glm::transpose(glm::mat3(model)));
    shader.set("normalMat", normalMat);
    quad.render();

    model = glm::mat4(1.0f);
    shader.set("model", model);
    normalMat = glm::inverse(glm::transpose(glm::mat3(model)));
    shader.set("normalMat", normalMat);
    cube.render();

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 2.0f, 0.0f));
    shader.set("model", model);
    normalMat = glm::inverse(glm::transpose(glm::mat3(model)));
    shader.set("normalMat", normalMat);


    sphere.render();

}

void render(const Geometry& quad, const Geometry& cube, const Geometry& sphere, const Geometry& light, const Geometry& visor1, const Geometry& visor2,
    const Shader& s_phong, const Shader& s_ligth, const Shader& s_depth, const Shader& s_debug,
    const Texture& t_albedo, const Texture& t_specular, const uint32_t fbo1, const uint32_t fbo_texture1, const uint32_t fbo2, const uint32_t fbo_texture2) {

    //FIRST PASS
    glBindFramebuffer(GL_FRAMEBUFFER, fbo1);
    glViewport(0, 0, k_shadow_width, k_shadow_height);
    glClear(GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    const glm::mat4 lightProjection = glm::perspective<float>(glm::radians(105.0f), 1.0f, k_shadow_near, k_shadow_far);
    const glm::mat4 lightView = glm::lookAt(spotLightPos[0], spotlightDirs[0], glm::vec3(0.0f, 1.0f, 0.0f));
    
    const glm::mat4 lightSpaceMatrix = lightProjection * lightView;

    s_depth.use();
    s_depth.set("lightSpaceMatrix", lightSpaceMatrix);
    //glCullFace(GL_FRONT);
    renderScene(s_depth,  quad, cube, sphere, light, t_albedo, t_specular);
    //glCullFace(GL_BACK);

//SECOND PASS
    glBindFramebuffer(GL_FRAMEBUFFER, fbo2);
    glViewport(0, 0, k_shadow_width, k_shadow_height);
    glClear(GL_DEPTH_BUFFER_BIT);

    const glm::mat4 lightProjection2 = glm::perspective<float>(glm::radians(105.0f), 1.0f, k_shadow_near, k_shadow_far);
    const glm::mat4 lightView2 = glm::lookAt(spotLightPos[1], spotlightDirs[1], glm::vec3(0.0f, 1.0f, 0.0f));

    const glm::mat4 lightSpaceMatrix2 = lightProjection2 * lightView2;

    s_depth.use();
    s_depth.set("lightSpaceMatrix", lightSpaceMatrix2);
    //glCullFace(GL_FRONT);
    renderScene(s_depth, quad, cube, sphere, light, t_albedo, t_specular);
    //glCullFace(GL_BACK);

//THIRD PASS
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, Window::instance()->getWidth(), Window::instance()->getHeight());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 proj = glm::perspective(glm::radians(camera.getFOV()), static_cast<float>(Window::instance()->getWidth()) / Window::instance()->getHeight(), 0.1f, 100.0f);

    s_ligth.use();
    glm::vec3 colorLigth = glm::vec3(0.7f, 0.7f, 0.7f);
    //SpotLigths
    int i = 0;
    for (const auto& spotPos : spotLightPos) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, spotPos);
        s_ligth.set("model", model);
        s_ligth.set("view", view);
        s_ligth.set("proj", proj);
        s_ligth.set("lightColor", colorLigth);

        light.render();
        i++;
    }

    s_phong.use();

    s_phong.set("view", view);
    s_phong.set("proj", proj);

    s_phong.set("viewPos", camera.getPosition());

    //SpotLigth 1
    s_phong.set("spotLight[0].position", spotLightPos[0]);
    s_phong.set("spotLight[0].direction", spotlightDirs[0]);
    s_phong.set("spotLight[0].ambient", 0.1f, 0.1f, 0.1f);
    s_phong.set("spotLight[0].diffuse", 0.6f, 0.6f, 0.6f);
    s_phong.set("spotLight[0].specular", 1.0f, 1.0f, 1.0f);
    s_phong.set("spotLight[0].constant", 1.0f);
    s_phong.set("spotLight[0].linear", 0.1f);
    s_phong.set("spotLight[0].quadratic", 0.064f);
    s_phong.set("spotLight[0].cutOff", glm::cos(glm::radians(45.0f)));
    s_phong.set("spotLight[0].outerCutOff", glm::cos(glm::radians(55.0f)));
    //SpotLigth 2
    s_phong.set("spotLight[1].position", spotLightPos[1]);
    s_phong.set("spotLight[1].direction", spotlightDirs[1]);
    s_phong.set("spotLight[1].ambient", 0.1f, 0.1f, 0.1f);
    s_phong.set("spotLight[1].diffuse", 0.6f, 0.6f, 0.6f);
    s_phong.set("spotLight[1].specular", 1.0f, 1.0f, 1.0f);
    s_phong.set("spotLight[1].constant", 1.0f);
    s_phong.set("spotLight[1].linear", 0.1f);
    s_phong.set("spotLight[1].quadratic", 0.064f);
    s_phong.set("spotLight[1].cutOff", glm::cos(glm::radians(45.0f)));
    s_phong.set("spotLight[1].outerCutOff", glm::cos(glm::radians(55.0f)));

    s_phong.set("material.shininess", 32);

    s_phong.set("lightSpaceMatrix[0]", lightSpaceMatrix);
    s_phong.set("lightSpaceMatrix[1]", lightSpaceMatrix2);
    //s_phong.set("lightSpaceMatrix2", lightSpaceMatrix2);

    s_debug.use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, fbo_texture1);
    s_debug.set("depthMap", 0);

    visor1.render();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, fbo_texture2);
    s_debug.set("depthMap", 0);

    visor2.render();

    s_phong.use();

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, fbo_texture1);
    s_phong.set("depthMap[0]", 2);
    glBindTexture(GL_TEXTURE_2D, fbo_texture2);
    s_phong.set("depthMap[1]", 2);

    /*glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, Window::instance()->getWidth(), Window::instance()->getHeight());
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);*/

    renderScene(s_phong, quad, cube, sphere, light, t_albedo, t_specular);

}

int main(int, char* []) {
    Window* window = Window::instance();
    window->setWidth(800);
    window->setHeight(600);

    glClearColor(0.0f, 0.3f, 0.6f, 1.0f);

    const Shader s_phong("../projects/EJ14_02/phong.vs", "../projects/EJ14_02/blinn.fs");
    const Shader s_light("../projects/EJ14_02/light.vs", "../projects/EJ14_02/light.fs");
    const Shader s_depth("../projects/EJ14_02/depth.vs", "../projects/EJ14_02/depth.fs");
    const Shader s_debug("../projects/EJ14_02/debug.vs", "../projects/EJ14_02/debug.fs");
    const Texture t_albedo("../assets/textures/bricks_albedo.png", Texture::Format::RGB);
    const Texture t_specular("../assets/textures/bricks_specular.png", Texture::Format::RGB);
    const Quad quad(2.0f);
    const Cube cube(1.0f);
    const Sphere sphere(1.0f, 25, 25);
    const Sphere light(0.25f, 20, 20);
    const Quad visor1(0.5f, 2);
    const Quad visor2(0.5f, 4);

    RenderFBO fbo_depth1(k_shadow_height, k_shadow_width, 1);
    RenderFBO fbo_depth2(k_shadow_height, k_shadow_width, 1);

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
        render(quad, cube, sphere, light, visor1, visor2, s_phong, s_light, s_depth, s_debug, t_albedo, t_specular, fbo_depth1.getFBO(), fbo_depth1.getDepthMap(), fbo_depth2.getFBO(), fbo_depth2.getDepthMap());
        window->frame();
    }

    fbo_depth1.DeleteFBO();
    fbo_depth2.DeleteFBO();

    return 0;
}