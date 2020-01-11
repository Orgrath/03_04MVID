#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "engine/input.hpp"
#include "engine/window.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

void handleInput() {
    /*std::vector<std::pair<int, int>> keys = Input::instance()->getKeys();
    for (auto& key : keys) {
        std::cout << key.first << " - " << key.second << std::endl;
    }*/
}

bool checkShader(uint32_t shader) {
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cout << "Error Compiling Shader " << infoLog << std::endl;
        return false;
    }
    return true;
}

bool checkProgram(uint32_t program) {
    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        std::cout << "Error Linking Program " << infoLog << std::endl;
        return false;
    }
    return true;
}

uint32_t createProgram() {
    const char* vertexShaderSource = "#version 330 core\n"
        "layout (location=0) in vec3 aPos;\n"
        "void main() {\n"
        "    gl_Position = vec4(aPos, 1.0);\n"
        "}\0";
    const char* fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main() {\n"
        "    FragColor = vec4(0.6, 0.6, 0.1, 1.0);\n"
        "}\0";

    const uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    checkShader(vertexShader);

    const uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    checkShader(fragmentShader);

    const uint32_t program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    checkProgram(program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}

uint32_t createVertexData(uint32_t* VBO, uint32_t* EBO) {
    //El angulo cambia cada 2 ciclos
    //Las x cambia cada 2 ciclos
    //Las y cambia a cada ciclo
    float PI = acos(-1);
    float vertices[21]; 
    //uint32_t indices[18];
    float radio = 0.5f;

    //iniciamos el punto central
    vertices[0] = 0.0f; vertices[1] = 0.0f; vertices[2] = 0.0f;
    //std::cout << " vertices: (" << vertices[0] << "," << vertices[1] << "," << vertices[2] << ")" << std::endl;
    //Continuamos con el resto de puntos
    int i = 3;//contador ascedente
    int j = 20;//contador descendente
    //int k = 0;
    int m;
    int n = 0;
    int angulo = 0;
    int incrementoAngulo = 360 / 6;
    int signo;
    int contador = 3;
    int CambioAngulo = 2;
    //int filaA = 1;
    //int filaD = 6;
    while (contador > 0) {
        float theta = angulo * PI / 180;
        if (contador == 2) { signo = 1; } else signo = -1;

        if (CambioAngulo > 1) { //Solo se ejecutará en el primer ciclo
            vertices[i] = radio * cos(0);
            i++;
            vertices[i] = 0.0f;
            i++;
            vertices[i] = 0.0f;
            i++;
            //Cálculo camino derecha-izquierda
            vertices[j] = 0.0f;
            j--;
            vertices[j] = 0.0f;
            j--;
            vertices[j] = (-1) * radio * cos(0);
            j--;
            angulo = angulo + incrementoAngulo;
        }
        else //Solo segundo y tercer ciclo
        {
            m = 5 - n;
            //Cálculo camino izquierda-derecha
            vertices[i] = signo * radio * cos(theta);
            i++;
            vertices[i] = radio * sin(theta);
            i++;
            vertices[i] = 0.0f;
            i++;
            //Cálculo camino derecha-izquierda
            vertices[j] = 0.0f;
            j--;
            vertices[j] = (-1) * radio * sin(theta);
            j--;
            vertices[j] = signo * radio * cos(theta); 
            j--;
            //Calculo de indices
            /*indices[k]     = 0;
            indices[k + 3] = 0;

            indices[k + 1] = 6 - m;
            if ((6 - m) != 1) { m--;}
            indices[k + 5] = 6 - m;
            m--;
            indices[k + 2] = 6 - m;
            m--;
            indices[k + 4] = 6 - m;
            n++;
            std::cout << " indice: (" << indices[k] << "," << indices[k+1] << "," << indices[k+2] << ")" << std::endl;
            std::cout << " indice: (" << indices[k+3] << "," << indices[k + 4] << "," << indices[k + 5] << ")" << std::endl;
            k = k + 6;*/
        };
        contador--;
        CambioAngulo--;
        //std::cout << " vertices: (" << vertices[i-3] << "," << vertices[i-2] << "," << vertices[i-1] << ")" << std::endl;
        //std::cout << " vertices: (" << vertices[j+1] << "," << vertices[j + 2] << "," << vertices[j+3] << ")" << std::endl;
    };
    n++;
    //std::cout << " m: " << m << std::endl;
    //std::cout << " n: " << n << std::endl;
    //Calculo de indices
    /*m = 5 - n;
    indices[k] = 0;
    indices[k + 3] = 0;
    indices[k + 1] = 6 - m;
    m--;
    indices[k + 5] = 6 - m;
    m--;
    indices[k + 2] = 6 - m;
    indices[k + 4] = 6 - m;
    std::cout << " indice: (" << indices[k] << "," << indices[k + 1] << "," << indices[k + 2] << ")" << std::endl;
    std::cout << " indice: (" << indices[k + 3] << "," << indices[k + 4] << "," << indices[k + 5] << ")" << std::endl;*/

    uint32_t indices[] = {
        0,1,2,
        0,2,3,
        0,3,6,
        0,6,4,
        0,4,5,
        0,5,1
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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return VAO;
}

void render(uint32_t VAO, uint32_t program) {
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(program);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, nullptr);
}

int main(int, char* []) {
    Window* window = Window::instance();

    glClearColor(0.0f, 0.3f, 0.6f, 1.0f);

    uint32_t VBO, EBO;
    const uint32_t VAO = createVertexData(&VBO, &EBO);
    const uint32_t program = createProgram();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);//GL_FILL - GL_LINE

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    while (window->alive()) {
        handleInput();
        render(VAO, program);
        window->frame();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glDeleteProgram(program);

    return 0;
}