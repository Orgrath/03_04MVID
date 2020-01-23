#include <glad/glad.h>

#include "engine/window.hpp"
#include "engine/shader.hpp"

#include "engine/texture.hpp"
#include "engine/geometry/cube.hpp"
#include "engine/geometry/quad.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

void handleInput() {/*Intentionally Left BLank*/ }

void render(const Geometry& geom1, const Geometry& geom2, const Shader& shader, Texture& tex1, Texture& tex2) {
    glClear(GL_COLOR_BUFFER_BIT);

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, -0.65f, -3.0f));
    //view = glm::rotate(view, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    glm::mat4 proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(2.25f, 2.0f, 1.0f));
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(-1.0f, 0.0f, 0.0f));

    glm::vec3 cubePositions[] = {
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(0.5f, 0.5f, 0.5f),
        glm::vec3(0.0f, 0.0f, 0.0f),
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
    shader.set("view", view);
    shader.set("proj", proj);  //TODO const mat4

    tex1.use(shader, "tex", 0);

    for (uint8_t i = 0; i < 5; i++) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);
        model = glm::scale(model, cubeScales[i]);
        //model = glm::rotate(model, glm::radians(75.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        //float angle = 10.0f + (20.0f * i);
        //model1 = glm::rotate(model1, static_cast<float>(glfwGetTime())* glm::radians(angle), glm::vec3(0.5f, 1.0f, 0.0f));
        shader.set("model", model);

        geom1.render();
    }

}


void render(const Geometry& geom, const Shader& shader, Texture& tex) {
    glClear(GL_COLOR_BUFFER_BIT);

    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),
        glm::vec3(-1.3f, 1.0f, -1.5f)
    };

    /*glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, static_cast<float>(glfwGetTime())* glm::radians(20.0f), glm::vec3(0.5f, 1.0f, 0.0f));*/

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    glm::mat4 proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    shader.use();

    tex.use(shader, "tex", 0);

    shader.set("view", view);
    shader.set("proj", proj);  //TODO const mat4



    for (uint8_t i = 0; i < 10; i++) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);
        float angle = 10.0f + (20.0f * i);
        model = glm::rotate(model, static_cast<float>(glfwGetTime())* glm::radians(angle), glm::vec3(0.5f, 1.0f, 0.0f));
        shader.set("model", model);

        geom.render();
    }

}

void renderQuad(const Geometry& geom, const Shader& shader, Texture& tex) {
    glClear(GL_COLOR_BUFFER_BIT);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(2.25f, 2.0f, 1.0f));
    model = glm::translate(model, glm::vec3(0.0f,-0.25f, -1.5f));
    model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::rotate(model, glm::radians(75.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    glm::mat4 proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    shader.use();

    tex.use(shader, "tex", 0);

    shader.set("view", view);
    shader.set("model", model);
    shader.set("proj", proj);  //TODO const mat4

    geom.render();

}

int main(int, char* []) {
    Window* window = Window::instance();

    glClearColor(0.0f, 0.3f, 0.6f, 1.0f);

    const Shader shader("../projects/AG05/vertex.vs", "../projects/AG05/fragment.fs");
    //const Cube cube(1.0f);
    const Cube cube(0.2f);
    const Quad quad(3.0f);

    Texture tex("../assets/textures/blue_blocks.jpg", Texture::Format::RGB);
    Texture tex1("../assets/textures/bricks_arrow.jpg", Texture::Format::RGB);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    while (window->alive()) {
        handleInput();
        //renderQuad(quad, shader, tex1);
        //render(cube, shader, tex);
        render(cube, quad, shader, tex, tex1);
        window->frame();
    }

    return 0;
}