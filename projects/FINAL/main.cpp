#include <GLFW/glfw3.h>
#include <iostream>

#include "engine/camera.hpp"
#include "engine/input.hpp"
#include "engine/model.hpp"
#include "engine/player.hpp"


Camera camera(glm::vec3(0.0f, 5.0f, 0.0f));
float lastFrame = 0.0f;
const float velocity = 0.005f;
bool game_is_running = true;

void handle_input(float dt) {
    Input* input = Input::instance();

    if (input->isKeyPressed(GLFW_KEY_W)) {
        //camera.handleKeyboard(Camera::Movement::Forward, dt + velocity);
    }
    if (input->isKeyPressed(GLFW_KEY_S)) {
        //camera.handleKeyboard(Camera::Movement::Backward, dt + velocity);
    }
    if (input->isKeyPressed(GLFW_KEY_A)) {
        //camera.handleKeyboard(Camera::Movement::Left, dt + velocity);
    }
    if (input->isKeyPressed(GLFW_KEY_D)) {
        //camera.handleKeyboard(Camera::Movement::Right, dt + velocity);
    }
    if (input->isKeyPressed(GLFW_KEY_ESCAPE)) {
        game_is_running = false;
    }
    /*if (input->isKeyPressed(GLFW_KEY_SPACE)) {
        camera.handleKeyboard(Camera::Movement::Up, dt + velocity);
    }
    if (input->isKeyPressed(GLFW_KEY_LEFT_CONTROL)) {
        camera.handleKeyboard(Camera::Movement::Down, dt + velocity);
    }*/
}

void update_game() {
}

void display_game() {
}

int main(int, char* []) {

    const Model nave("../assets/models/FINAL/Futuristic_combat_jet/Futuristic combat jet.obj");
    const float currentFrame = glfwGetTime();
    const float deltaTime = currentFrame - lastFrame;
    Player player(nave, 0.0f, 0.0f, 0.0f, 3);
    lastFrame = currentFrame;

    while (game_is_running) {
        handle_input(deltaTime);
        update_game();
        display_game();
    }
}