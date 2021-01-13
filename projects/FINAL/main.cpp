#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "engine/shader.hpp"
#include "engine/input.hpp"
#include "engine/texture.hpp"
#include "engine/camera.hpp"
#include "engine/player.hpp"
#include "engine/geometry/quad.hpp"
#include "engine/geometry/cube.hpp"

#include <iostream>

Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));
Player player(glm::vec3(0.0f, 0.5f, 0.0f));
const float velocity = 0.005f;

float lastFrame = 0.0f;
float lastX, lastY;
bool firstMouse = true;

void handleInput_debug(float dt) {
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

void handleInput(Player player, float dt) {
    Input* input = Input::instance();

    if (input->isKeyPressed(GLFW_KEY_W)) {
        player.handleKeyboard(Player::Movement::Forward, dt + velocity);
    }
    if (input->isKeyPressed(GLFW_KEY_A)) {
        player.handleKeyboard(Player::Movement::Left, dt + velocity);
    }
    if (input->isKeyPressed(GLFW_KEY_D)) {
        player.handleKeyboard(Player::Movement::Right, dt + velocity);
    }
    if (input->isKeyPressed(GLFW_KEY_S)) {
        player.handleKeyboard(Player::Movement::Backward, dt + velocity);
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

void renderScene(const Shader& shader, const Shader& base,
    //const Geometry& quad, Geometry& hitbox,
    //const Geometry& fondo, Player& player,
    Player& player,
    const Texture& t_albedo, const Texture& t_specular) {

    //t_albedo.use(shader, "material.diffuse", 0);
    //t_specular.use(shader, "material.specular", 1);

    glm::mat4 model = glm::mat4(1.0f);
    //shader.set("model", model);
    glm::mat3 normalMat = glm::inverse(glm::transpose(glm::mat3(model)));
    //shader.set("normalMat", normalMat);
    //fondo.render();

    base.use();
    //model = glm::mat4(1.0f);
    base.set("model", model);
    //normalMat = glm::inverse(glm::transpose(glm::mat3(model)));
    model = glm::translate(model, player.getPoshitBox());
    std::cout << "X:" << player.getPoshitBox().x << std::endl;
    std::cout << "Y:" << player.getPoshitBox().y << std::endl;
    std::cout << "Z:" << player.getPoshitBox().z << std::endl;
    //hitbox.render();
    player.getHitbox().render();

}

//void render(const Geometry& quad, const Geometry& hitbox,
//void render(const Geometry& quad, Player& player,
void render(Player& player,
    const Shader& s_phong, const Shader& s_base,
    const Texture& t_albedo, const Texture& t_specular){

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, Window::instance()->getWidth(), Window::instance()->getHeight());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 proj = glm::perspective(glm::radians(camera.getFOV()), static_cast<float>(Window::instance()->getWidth()) / Window::instance()->getHeight(), 0.1f, 100.0f);

    s_base.use();
    s_base.set("view", view);
    s_base.set("proj", proj);
    s_base.set("base.color", glm::vec3(1.0f, 0.0f, 0.0f));
    s_base.set("base.transparency", 0.5f);

    //s_phong.use();
    //s_phong.set("view", view);
    //s_phong.set("proj", proj);
    //s_phong.set("light.ambient", 0.5f, 0.5f, 0.5f);

    //renderScene(s_phong, s_base, quad, hitbox, t_albedo, t_specular);
    //renderScene(s_phong, s_base, quad, player, t_albedo, t_specular);
    renderScene(s_phong, s_base, player, t_albedo, t_specular);

}

int main(int, char* []) {

    Window* window = Window::instance();
    window->setWidth(800);
    window->setHeight(600);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	const Shader s_phong("../projects/FINAL/phong.vs", "../projects/FINAL/blinn.fs");
    const Shader s_base("../projects/FINAL/phong_base.vs", "../projects/FINAL/blinn_base.fs");
	const Texture t_albedo("../assets/textures/bricks_albedo.png", Texture::Format::RGB);
	const Texture t_specular("../assets/textures/bricks_specular.png", Texture::Format::RGB);
    const Quad hitbox(1.0f);
	//const Quad fondo(0.5f);

    player.setHitbox(hitbox);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

	Input::instance()->setKeyPressedCallback(onKeyPress);
	Input::instance()->setMouseMoveCallback(onMouseMoved);
	Input::instance()->setScrollMoveCallback(onScrollMoved);

    while (window->alive()) {
        const float currentFrame = glfwGetTime();
        const float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        //handleInput_debug(deltaTime);
        handleInput(player, deltaTime);
        //render(fondo, player.getHitbox(), s_phong, s_base, t_albedo, t_specular);
        //render(fondo, player, s_phong, s_base, t_albedo, t_specular);
        render(player, s_phong, s_base, t_albedo, t_specular);
        window->frame();
    }

    return 0;

}