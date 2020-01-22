#include "engine/geometry/cubepolar.hpp"
#include <glm/gtc/matrix_transform.hpp>

#include <stdio.h>

CubePolar::CubePolar(float radio, glm::vec3 inicio) : _radio(radio), _inicio(inicio) {
    _nVertices = 6 * 2 * 3;   //6 faces * 2 triangles * 3 vertices;
    _nElements = _nVertices;

    int i = 0, j = 0;
    uint32_t k = 0;
    int contador = 1;
    float theta;
    float omega;
    const float ainc = 90.0f;
    const int tindices = 6 * 6;      //6 faces * 6 vertices;
    const int vertices = 6 * 4 * 3; //6 faces * 4 vertices * 3 coordenadas;
    float positions[vertices];
    uint32_t indices[tindices];
    float ae;
    float vz;
    float rectA;

     while (j < tindices) {

        if (j < 12) { //Front and back

            //Iniciamos los valores para el Front
            if (j == 0) { 
                theta = 225.0f;
                omega = 45.0f;
                ae = 1.0f;
                rectA = 15.0f;
            }

            //Valores de los angulos dependiendo de la iteración del cálculo del Quad
            if (contador > 1 && contador <= 4) {
                theta = theta + (ae * ainc);
            }
            else if (contador > 4) {//Se activa cuando ya hemos calculado el Front y preparamos para calcular el Back
                theta = 315.0f;
                omega = 135.0f;
                ae = ae * (-1);
                rectA = -15.0f;
                contador = 1;
            }

            //printf("Contador: %d\n", contador);
            //printf("J: %d - K: %u\n", j, k);
            //printf("theta: %f - Omega: %f\n", theta, omega);

            //Front and back
            positions[i] = (radio * sin(glm::radians(omega)) * cos(glm::radians(theta))) + inicio.x; // x
            //printf("punto[%f,", positions[i]);
            i++;
            positions[i] = (radio * sin(glm::radians(omega)) * sin(glm::radians(theta))) + inicio.y; // y
            //printf(" %f,", positions[i]);
            i++;
            positions[i] = (radio * cos(glm::radians(omega + rectA))) + inicio.z;                        // z
            //printf(" %f]\n", positions[i]);
            i++;
        }
        else if (j >= 12 && j < 24) { //Right and Left

             //Iniciamos los valores para el Rigth
            if (j == 12) {
                theta = 315.0f;
                omega = 45.0f;
                rectA = 15.0f;
                ae = 1.0f;
                contador = 1;//Reiniciamos contador para el nuevo calculo
                ae = ae * (-1);
            }

            //Valores de los angulos dependiendo de la iteración del cálculo del Quad
            if (contador > 1 && contador <= 4){//Incrementamos el angulo theta
                theta = theta + (ae * ainc);
            }
            else if (contador > 4) {//Se activa cuando ya hemos calculado el Rigth y preparamos para calcular el Left
                theta = 225.0f;
                omega = 135.0f;
                rectA = -15.0f;
                ae = ae * (-1);
                contador = 1;
            }

            //printf("Contador: %d\n", contador);
            //printf("i: %d\n", i);
            //printf("theta: %f - Omega: %f\n", theta, omega);

            //Rigth and Left
            positions[i]   = (radio * cos(glm::radians(omega + rectA))) + inicio.x;                          // x
            //printf("punto[%f,", positions[i]);
            i++;
            positions[i] = (radio * sin(glm::radians(omega)) * sin(glm::radians(theta))) + inicio.y; // y
            //printf(" %f,", positions[i]);
            i++;
            positions[i] = (radio * sin(glm::radians(omega)) * cos(glm::radians(theta))) + inicio.z; // z
            //printf(" %f]\n", positions[i]);
            i++;

        }
        else if (j >= 24 && j < 35){ //Top and Bottom

            //Iniciamos los valores para el Top
            if (j == 24) {
                theta = 135.0f;
                omega = 45.0f;
                contador = 1;//Reiniciamos contador para el nuevo calculo
                rectA = 15.0f;
                ae = ae * (-1);
                vz = 1.0f;
            }

            //Valores de los angulos dependiendo de la iteración del cálculo del Quad
            if (contador > 1 && contador <= 2) {//Incrementamos el angulo theta
                theta = theta + (ae * ainc);
            }
            else if (contador == 3) {
                ae = ae * (-1);
                omega = omega + (ae * ainc);
                rectA = rectA * -1.0f;
                vz = -1.0f;
            }
            else if (contador == 4) {
                theta = theta + (ae * ainc);
            }
            else if (contador > 4) {//Se activa cuando ya hemos calculado el top y preparamos para calcular el bottom
                theta = 225.0f;
                contador = 1;
                vz = 1.0f;
            }

            //printf("Contador: %d\n", contador);
            //printf("i: %d\n", i);
            //printf("theta: %f - Omega: %f\n", theta, omega);

            //top and bottom
            positions[i] = (radio * sin(glm::radians(omega)) * cos(glm::radians(theta))) + inicio.x;   // x
            //printf("punto[%f,", positions[i]);
            i++;
            positions[i] = vz * (radio * cos(glm::radians(omega + rectA))) + inicio.y;                        // y
            //printf(" %f,", positions[i]);
            i++;
            positions[i] = vz * (radio * sin(glm::radians(omega)) * sin(glm::radians(theta))) + inicio.z; // z
            //printf(" %f]\n", positions[i]);
            i++;
        }
        if (contador < 4) {
            indices[j] = k;
            //printf("indice[%d]= %u\n", j, indices[j]);
            j++;
            k++;
        }
        else {
            //printf("Calculo del 2 triangulo...\n");
            indices[j] = k - 3;
            //printf("indice[%d]= %u\n", j, indices[j]);
            j++;
            indices[j] = k - 1;
            //printf("indice[%d]= %u\n", j, indices[j]);
            j++;
            indices[j] = k;
            //printf("indice[%d]= %u\n", j, indices[j]);
            j++;
            k++;
        }
        contador++;
        //printf("\n");
    }

    float uvs[] = { 0.0f, 0.0f,   //front
                    1.0f, 0.0f,
                    1.0f, 1.0f,
                    0.0f, 1.0f,

                    0.0f, 0.0f,   //back
                    1.0f, 0.0f,
                    1.0f, 1.0f,
                    0.0f, 1.0f,

                    0.0f, 0.0f,   //right
                    1.0f, 0.0f,
                    1.0f, 1.0f,
                    0.0f, 1.0f,

                    0.0f, 0.0f,   //left
                    1.0f, 0.0f,
                    1.0f, 1.0f,
                    0.0f, 1.0f,

                    0.0f, 0.0f,   //bottom
                    1.0f, 0.0f,
                    1.0f, 1.0f,
                    0.0f, 1.0f,

                    0.0f, 0.0f,   //top
                    1.0f, 0.0f,
                    1.0f, 1.0f,
                    0.0f, 1.0f };


    float normals[] = { 
                    0.0f, 0.0f, 1.0f,  //front
                    0.0f, 0.0f, 1.0f,
                    0.0f, 0.0f, 1.0f,
                    0.0f, 0.0f, 1.0f,

                    0.0f, 0.0f, -1.0f,  //back
                    0.0f, 0.0f, -1.0f,
                    0.0f, 0.0f, -1.0f,
                    0.0f, 0.0f, -1.0f,

                    1.0f, 0.0f, 0.0f,  //right
                    1.0f, 0.0f, 0.0f,
                    1.0f, 0.0f, 0.0f,
                    1.0f, 0.0f, 0.0f,

                    -1.0f, 0.0f, 0.0f,  //left
                    -1.0f, 0.0f, 0.0f,
                    -1.0f, 0.0f, 0.0f,
                    -1.0f, 0.0f, 0.0f,

                    0.0f, -1.0f, 0.0f,  //bottom
                    0.0f, -1.0f, 0.0f,
                    0.0f, -1.0f, 0.0f,
                    0.0f, -1.0f, 0.0f,

                    0.0f, 1.0f, 0.0f,  //top
                    0.0f, 1.0f, 0.0f,
                    0.0f, 1.0f, 0.0f,
                    0.0f, 1.0f, 0.0f };

    uploadData(positions, uvs, normals, indices);
}