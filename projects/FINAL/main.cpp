#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "engine/camera.hpp"
#include "engine/input.hpp"
#include "engine/shader.hpp"
#include "engine/model.hpp"
#include "engine/player.hpp"
#include "engine/geometry/cube.hpp"


Camera camera(glm::vec3(0.0f, 5.0f, 0.0f));
float lastFrame = 0.0f;
const float velocity = 0.005f;
bool game_is_running = true;

void handle_input(Player pj, float dt) {
    Input* input = Input::instance();

    if (input->isKeyPressed(GLFW_KEY_W)) {
        //camera.handleKeyboard(Camera::Movement::Forward, dt + velocity);
        pj.handleKeyboard(Player::Movement::Forward, dt + velocity);
    }
    if (input->isKeyPressed(GLFW_KEY_S)) {
        //camera.handleKeyboard(Camera::Movement::Backward, dt + velocity);
        pj.handleKeyboard(Player::Movement::Backward, dt + velocity);
    }
    if (input->isKeyPressed(GLFW_KEY_A)) {
        //camera.handleKeyboard(Camera::Movement::Left, dt + velocity);
        pj.handleKeyboard(Player::Movement::Left, dt + velocity);
    }
    if (input->isKeyPressed(GLFW_KEY_D)) {
        //camera.handleKeyboard(Camera::Movement::Right, dt + velocity);
        pj.handleKeyboard(Player::Movement::Right, dt + velocity);
    }
    if (input->isKeyPressed(GLFW_KEY_SPACE)) {

    }
    if (input->isKeyPressed(GLFW_KEY_ESCAPE)) {
        game_is_running = false;
    }
}

void update_game() {
}

void renderScene(const Shader& shader, Player& pj) {

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat3 normalMat = glm::inverse(glm::transpose(glm::mat3(model)));
    shader.set("model", model);
    shader.set("normalMat", normalMat);
    pj.getHitbox().render();

}

void display_game(Player& pj, const Shader& s_phong) {
    glClear(GL_COLOR_BUFFER_BIT);

    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 proj = glm::perspective(glm::radians(camera.getFOV()), static_cast<float>(Window::instance()->getWidth()) / Window::instance()->getHeight(), 0.1f, 100.0f);

    s_phong.use();

    s_phong.set("view", view);
    s_phong.set("proj", proj);

    s_phong.set("viewPos", camera.getPosition());

    s_phong.set("light.position", 0.0f, 10.0f, 0.0f);
    s_phong.set("light.ambient", 0.6f, 0.6f, 0.6f);

    renderScene(s_phong, pj);

}

int main(int, char* []) {
    Window* window = Window::instance();
    window->setWidth(800);
    window->setHeight(600);

    const Shader s_phong("../projects/FINAL/phong.vs", "../projects/FINAL/blinn.fs");
    const Model nave("../assets/models/FINAL/Futuristic_combat_jet/Futuristic combat jet.obj");
    const Cube hitbox(1.0f);
    const float currentFrame = glfwGetTime();
    const float deltaTime = currentFrame - lastFrame;
    Player player(nave, hitbox, 0.0f, 0.0f, 0.0f, 3);
    lastFrame = currentFrame;

    while (game_is_running) {
        handle_input(player, deltaTime);
        update_game();
        display_game(player, s_phong);
    }
}