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

Quad::Quad(float size, int8_t mode) : _size(size) {
    _nVertices = 1 * 2 * 3;  //1 face * 2 triangles * 3 vertices
    _nElements = _nVertices;

    float positions[18];
    const float half = size / 2.0f;

    const float diff = 1.0f - half;

    switch (mode)
    {
    case 0:
        positions[0] = half - diff; positions[1] = half - diff; positions[2] = 0.0f;    //upper right triangle
        positions[3] = half - diff; positions[4] = -half - diff; positions[5] = 0.0f;
        positions[6] = -half - diff; positions[7] = half - diff; positions[8] = 0.0f;

        positions[9] = half - diff; positions[10] = -half - diff; positions[11] = 0.0f;   //lower left triangle
        positions[12] = -half - diff; positions[13] = half - diff; positions[14] = 0.0f;
        positions[15] = -half - diff; positions[16] = -half - diff; positions[17] = 0.0f;

        break;
    case 1:
        positions[0] = half - diff; positions[1] = half; positions[2] = 0.0f;    //upper right triangle
        positions[3] = half - diff; positions[4] = -half; positions[5] = 0.0f;
        positions[6] = -half - diff; positions[7] = half; positions[8] = 0.0f;

        positions[9] = half - diff; positions[10] = -half; positions[11] = 0.0f;   //lower left triangle
        positions[12] = -half - diff; positions[13] = half; positions[14] = 0.0f;
        positions[15] = -half - diff; positions[16] = -half; positions[17] = 0.0f;

        break;
    case 2:
        positions[0] = half - diff; positions[1] = half + diff; positions[2] = 0.0f;    //upper right triangle
        positions[3] = half - diff; positions[4] = -half + diff; positions[5] = 0.0f;
        positions[6] = -half - diff; positions[7] = half + diff; positions[8] = 0.0f;

        positions[9] = half - diff; positions[10] = -half + diff; positions[11] = 0.0f;   //lower left triangle
        positions[12] = -half - diff; positions[13] = half + diff; positions[14] = 0.0f;
        positions[15] = -half - diff; positions[16] = -half + diff; positions[17] = 0.0f;
        break;
    case 3:
        positions[0] = half; positions[1] = half + diff; positions[2] = 0.0f;    //upper right triangle
        positions[3] = half; positions[4] = -half + diff; positions[5] = 0.0f;
        positions[6] = -half; positions[7] = half + diff; positions[8] = 0.0f;

        positions[9] = half; positions[10] = -half + diff; positions[11] = 0.0f;   //lower left triangle
        positions[12] = -half; positions[13] = half + diff; positions[14] = 0.0f;
        positions[15] = -half; positions[16] = -half + diff; positions[17] = 0.0f;
        break;
    case 4:
        positions[0] = half + diff; positions[1] = half + diff; positions[2] = 0.0f;    //upper right triangle
        positions[3] = half + diff; positions[4] = -half + diff; positions[5] = 0.0f;
        positions[6] = -half + diff; positions[7] = half + diff; positions[8] = 0.0f;

        positions[9] = half + diff; positions[10] = -half + diff; positions[11] = 0.0f;   //lower left triangle
        positions[12] = -half + diff; positions[13] = half + diff; positions[14] = 0.0f;
        positions[15] = -half + diff; positions[16] = -half + diff; positions[17] = 0.0f;
        break;
    case 5:
        positions[0] = half + diff; positions[1] = half; positions[2] = 0.0f;    //upper right triangle
        positions[3] = half + diff; positions[4] = -half; positions[5] = 0.0f;
        positions[6] = -half + diff; positions[7] = half; positions[8] = 0.0f;

        positions[9] = half + diff; positions[10] = -half; positions[11] = 0.0f;   //lower left triangle
        positions[12] = -half + diff; positions[13] = half; positions[14] = 0.0f;
        positions[15] = -half + diff; positions[16] = -half; positions[17] = 0.0f;
        break;
    case 6:
        positions[0] = half + diff; positions[1] = half - diff; positions[2] = 0.0f;    //upper right triangle
        positions[3] = half + diff; positions[4] = -half - diff; positions[5] = 0.0f;
        positions[6] = -half + diff; positions[7] = half - diff; positions[8] = 0.0f;

        positions[9] = half + diff; positions[10] = -half - diff; positions[11] = 0.0f;   //lower left triangle
        positions[12] = -half + diff; positions[13] = half - diff; positions[14] = 0.0f;
        positions[15] = -half + diff; positions[16] = -half - diff; positions[17] = 0.0f;
        break;
    case 7:
        positions[0] = half; positions[1] = half - diff; positions[2] = 0.0f;    //upper right triangle
        positions[3] = half; positions[4] = -half - diff; positions[5] = 0.0f;
        positions[6] = -half; positions[7] = half - diff; positions[8] = 0.0f;

        positions[9] = half; positions[10] = -half - diff; positions[11] = 0.0f;   //lower left triangle
        positions[12] = -half; positions[13] = half - diff; positions[14] = 0.0f;
        positions[15] = -half; positions[16] = -half - diff; positions[17] = 0.0f;
        break;
    default:
        positions[0] = half; positions[1] = half; positions[2] = 0.0f;    //upper right triangle
        positions[3] = half; positions[4] = -half; positions[5] = 0.0f;
        positions[6] = -half; positions[7] = half; positions[8] = 0.0f;

        positions[9] = half; positions[10] = -half; positions[11] = 0.0f;   //lower left triangle
        positions[12] = -half; positions[13] = half; positions[14] = 0.0f;
        positions[15] = -half; positions[16] = -half; positions[17] = 0.0f;

        break;
    }

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