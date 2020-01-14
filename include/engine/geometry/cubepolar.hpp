#ifndef __CUBEPOLAR_H__
#define __CUBEPOLAR_H__ 1

#include "geometry.hpp"
#include <glm/gtc/matrix_transform.hpp>

class CubePolar final : public Geometry {
    public:
        CubePolar() = delete;
        explicit CubePolar(float radio, glm::vec3 inicio);

    private:
        float _radio;
        glm::vec3 _inicio;
};
#endif