#include "engine/geometry/quad.hpp"

Quad::Quad(float size) : _size(size) {
    _nVertices = 1 * 2 * 3;  //1 face * 2 triangles * 3 vertices
    _nElements = _nVertices;

    const float half = size / 2.0f;

    float positions[] = { half, half, 0.0f,    //upper right triangle
                          half, -half, 0.0f,
                          -half, half, 0.0f,

                          half, -half, 0.0f,   //lower left triangle
                          -half, half, 0.0f,
                          -half, -half, 0.0f };

    float uvs[] = { 1.0f, 1.0f,
                    1.0f, 0.0f,
                    0.0f, 1.0f,

                    1.0f, 0.0f,
                    0.0f, 1.0f,
                    0.0f, 0.0f };

    float normals[] = { 0.0f, 0.0f, 1.0f,
                        0.0f, 0.0f, 1.0f,
                        0.0f, 0.0f, 1.0f,

                        0.0f, 0.0f, 1.0f,
                        0.0f, 0.0f, 1.0f,
                        0.0f, 0.0f, 1.0f };

    uint32_t indices[] = { 0, 2, 1,
                           3 , 4, 5 };

    uploadData(positions, uvs, normals, indices);
}

void Quad::setPosition(float xoffset, float yoffset) {
    float positions[] = { xoffset, yoffset, 0.0f,    //upper right triangle
                          xoffset, -yoffset, 0.0f,
                          -xoffset, yoffset, 0.0f,

                          xoffset, -yoffset, 0.0f,   //lower left triangle
                          -xoffset, yoffset, 0.0f,
                          -xoffset, -yoffset, 0.0f };
}