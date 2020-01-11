#include "engine/geometry/cube.hpp"
#include <glm/gtc/matrix_transform.hpp>

Cube::Cube(float size) : _size(size) {
    _nVertices = 6 * 2 * 3;   //6 faces * 2 triangles * 3 vertices;
    _nElements = _nVertices;

    const float half = size / 2.0f;

    float positions[] = { -half, -half, half,    //front
                          half, -half, half,
                          half, half, half,

                          -half, -half, half,
                          half, half, half,
                          -half, half, half,

                          half, -half, half,    //right
                          half, -half, -half,
                          half, half, -half,

                          half, -half, half,
                          half, half, -half,
                          half, half, half,

                          half, -half, -half,    //back
                          -half, -half, -half,
                          -half, half, -half,

                          half, -half, -half,
                          -half, half, -half,
                          half, half, -half,

                          -half, -half, -half,    //left
                          -half, -half, half,
                          -half, half, half,

                          -half, -half, -half,
                          -half, half, half,
                          -half, half, -half,

                          -half, -half, -half,    //bottom
                          half, -half, -half,
                          half, -half, half,

                          -half, -half, -half,
                          half, -half, half,
                          -half, -half, half,

                          -half, half, half,    //top
                          half, half, half,
                          half, half, -half,

                          -half, half, half,
                          half, half, -half,
                          -half, half, -half};

    float uvs[] = { 0.0f, 0.0f,   //front
                    1.0f, 0.0f,
                    1.0f, 1.0f,

                    0.0f, 0.0f,
                    1.0f, 1.0f,
                    0.0f, 1.0f,

                    0.0f, 0.0f,   //right
                    1.0f, 0.0f,
                    1.0f, 1.0f,

                    0.0f, 0.0f,
                    1.0f, 1.0f,
                    0.0f, 1.0f,

                    0.0f, 0.0f,   //back
                    1.0f, 0.0f,
                    1.0f, 1.0f,

                    0.0f, 0.0f,
                    1.0f, 1.0f,
                    0.0f, 1.0f,

                    0.0f, 0.0f,   //left
                    1.0f, 0.0f,
                    1.0f, 1.0f,

                    0.0f, 0.0f,
                    1.0f, 1.0f,
                    0.0f, 1.0f,

                    0.0f, 0.0f,   //bottom
                    1.0f, 0.0f,
                    1.0f, 1.0f,

                    0.0f, 0.0f,
                    1.0f, 1.0f,
                    0.0f, 1.0f,

                    0.0f, 0.0f,   //top
                    1.0f, 0.0f,
                    1.0f, 1.0f,

                    0.0f, 0.0f,
                    1.0f, 1.0f,
                    0.0f, 1.0f};

    float normals[] = { 0.0f, 0.0f, 1.0f,  //front
                        0.0f, 0.0f, 1.0f,
                        0.0f, 0.0f, 1.0f,

                        0.0f, 0.0f, 1.0f,
                        0.0f, 0.0f, 1.0f,
                        0.0f, 0.0f, 1.0f,

                        1.0f, 0.0f, 0.0f,  //right
                        1.0f, 0.0f, 0.0f,
                        1.0f, 0.0f, 0.0f,

                        1.0f, 0.0f, 0.0f,
                        1.0f, 0.0f, 0.0f,
                        1.0f, 0.0f, 0.0f,

                        0.0f, 0.0f, -1.0f,  //back
                        0.0f, 0.0f, -1.0f,
                        0.0f, 0.0f, -1.0f,

                        0.0f, 0.0f, -1.0f,
                        0.0f, 0.0f, -1.0f,
                        0.0f, 0.0f, -1.0f,

                        -1.0f, 0.0f, 0.0f,  //left
                        -1.0f, 0.0f, 0.0f,
                        -1.0f, 0.0f, 0.0f,

                        -1.0f, 0.0f, 0.0f,
                        -1.0f, 0.0f, 0.0f,
                        -1.0f, 0.0f, 0.0f,

                        0.0f, -1.0f, 0.0f,  //bottom
                        0.0f, -1.0f, 0.0f,
                        0.0f, -1.0f, 0.0f,

                        0.0f, -1.0f, 0.0f,
                        0.0f, -1.0f, 0.0f,
                        0.0f, -1.0f, 0.0f,

                        0.0f, 1.0f, 0.0f,  //top
                        0.0f, 1.0f, 0.0f,
                        0.0f, 1.0f, 0.0f,

                        0.0f, 1.0f, 0.0f,
                        0.0f, 1.0f, 0.0f,
                        0.0f, 1.0f, 0.0f};

    uint32_t indices[] = {  0, 1, 2, 3 , 4, 5,  //front
                            6, 7, 8, 9, 10, 11, //right
                            12, 13, 14, 15, 16, 17, //back
                            18, 19, 20, 21, 22, 23, //left
                            24, 25, 26, 27, 28, 29, //bottom
                            30, 31, 32, 33, 34, 35 }; //top

    uploadData(positions, uvs, normals, indices);
}

/*Versión polar*/
Cube::Cube(float radio, float ejex, float ejey, float ejez) : _size(radio), _ejex(ejex), _ejey(ejey), _ejez(ejez) {
    _nVertices = 6 * 2 * 3;   //6 faces * 2 triangles * 3 vertices;
    _nElements = _nVertices;

    int i = 0, j = 0, k = 0;
    int contador = 1;
    float theta = 225.0f;
    float omega;
    const float ainc = 90.0f;
    const int tindices = 6 * 4;      //6 faces * 4 vertices;
    const int vertices = 6 * 2 * 3; //6 faces * 2 triangles * 3 vertices;
    float positions[vertices];
    uint32_t indices[tindices];
    int x = 1, y= 1, z =1;


    while (j < tindices) {

        //Si ya hemos calculado los vertices inferiores, invertimos omega
        if (contador > 1) {
            omega = 45.0f;
        }else {
            omega = -45.0f;
        }

        if (j < 12) {

            if (contador == 4) {//Se activa cuando ya hemos calculado el Front y preparamos para calcular el Back
                theta = 225;
                z = z * (-1);
                contador = 0;
            }

            //Front and back
            positions[i] = (radio * sin(glm::radians(omega)) * cos(glm::radians(theta))) + ejex;   // x
            positions[i++] = (radio * sin(glm::radians(omega)) * sin(glm::radians(theta))) + ejey; // y
            positions[i++] = z * (radio * cos(glm::radians(omega))) + ejez;                        // z

            //break;
        }
        else if (j == 12 && j < 24) {

            if (contador == 4) {//Se activa cuando ya hemos calculado el Rigth y preparamos para calcular el Left
                theta = 225;
                x = x * (-1);
                contador = 0;
            }

            //Rigth and Left
            positions[i] = x * (radio * cos(glm::radians(omega))) + ejex;                          // x
            positions[i++] = (radio * sin(glm::radians(omega)) * sin(glm::radians(theta))) + ejey; // y
            positions[i++] = (radio * sin(glm::radians(omega)) * cos(glm::radians(theta))) + ejez; // z

            //break;
        }else if (j == 24 && j < 35){

            if (contador == 4) {//Se activa cuando ya hemos calculado el top y preparamos para calcular el bottom
                theta = 225;
                y = y * (-1);
                contador = 0;
            }

            //top and bottom
            positions[i] = (radio * sin(glm::radians(omega)) * cos(glm::radians(theta))) + ejex;   // x
            positions[i++] = y * (radio * cos(glm::radians(omega))) + ejey;                        // y
            positions[i++] = (radio * sin(glm::radians(omega)) * sin(glm::radians(theta))) + ejez; // z

            //break;
        }

        if (contador == 3) {
            indices[j] = k - 3;
            j++;
            indices[j] = k - 1;
            j++;
            indices[j] = k;
            j++;
            k++;
        }
        else {
            indices[j] = k;
            j++;
            k++;
        }
        
        contador++;
        theta = theta + ainc;

    }

    float uvs[] = { 0.0f, 0.0f,   //front
                    1.0f, 0.0f,
                    1.0f, 1.0f,

                    0.0f, 0.0f,
                    1.0f, 1.0f,
                    0.0f, 1.0f,

                    0.0f, 0.0f,   //right
                    1.0f, 0.0f,
                    1.0f, 1.0f,

                    0.0f, 0.0f,
                    1.0f, 1.0f,
                    0.0f, 1.0f,

                    0.0f, 0.0f,   //back
                    1.0f, 0.0f,
                    1.0f, 1.0f,

                    0.0f, 0.0f,
                    1.0f, 1.0f,
                    0.0f, 1.0f,

                    0.0f, 0.0f,   //left
                    1.0f, 0.0f,
                    1.0f, 1.0f,

                    0.0f, 0.0f,
                    1.0f, 1.0f,
                    0.0f, 1.0f,

                    0.0f, 0.0f,   //bottom
                    1.0f, 0.0f,
                    1.0f, 1.0f,

                    0.0f, 0.0f,
                    1.0f, 1.0f,
                    0.0f, 1.0f,

                    0.0f, 0.0f,   //top
                    1.0f, 0.0f,
                    1.0f, 1.0f,

                    0.0f, 0.0f,
                    1.0f, 1.0f,
                    0.0f, 1.0f };


    float normals[] = { 0.0f, 0.0f, 1.0f,  //front
                    0.0f, 0.0f, 1.0f,
                    0.0f, 0.0f, 1.0f,

                    0.0f, 0.0f, 1.0f,
                    0.0f, 0.0f, 1.0f,
                    0.0f, 0.0f, 1.0f,

                    1.0f, 0.0f, 0.0f,  //right
                    1.0f, 0.0f, 0.0f,
                    1.0f, 0.0f, 0.0f,

                    1.0f, 0.0f, 0.0f,
                    1.0f, 0.0f, 0.0f,
                    1.0f, 0.0f, 0.0f,

                    0.0f, 0.0f, -1.0f,  //back
                    0.0f, 0.0f, -1.0f,
                    0.0f, 0.0f, -1.0f,

                    0.0f, 0.0f, -1.0f,
                    0.0f, 0.0f, -1.0f,
                    0.0f, 0.0f, -1.0f,

                    -1.0f, 0.0f, 0.0f,  //left
                    -1.0f, 0.0f, 0.0f,
                    -1.0f, 0.0f, 0.0f,

                    -1.0f, 0.0f, 0.0f,
                    -1.0f, 0.0f, 0.0f,
                    -1.0f, 0.0f, 0.0f,

                    0.0f, -1.0f, 0.0f,  //bottom
                    0.0f, -1.0f, 0.0f,
                    0.0f, -1.0f, 0.0f,

                    0.0f, -1.0f, 0.0f,
                    0.0f, -1.0f, 0.0f,
                    0.0f, -1.0f, 0.0f,

                    0.0f, 1.0f, 0.0f,  //top
                    0.0f, 1.0f, 0.0f,
                    0.0f, 1.0f, 0.0f,

                    0.0f, 1.0f, 0.0f,
                    0.0f, 1.0f, 0.0f,
                    0.0f, 1.0f, 0.0f };

    uploadData(positions, uvs, normals, indices);
}