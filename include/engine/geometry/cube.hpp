#ifndef __CUBE_H__
#define __CUBE_H__ 1

#include "geometry.hpp"
//#include <glm/gtc/matrix_transform.hpp>

class Cube final : public Geometry {
    public:
        Cube() = delete;
        explicit Cube(float size);
        explicit Cube(float size, float ejex, float ejey, float ejez);

    private:
        float _size;
        float _ejex;
        float _ejey;
        float _ejez;
};
#endif