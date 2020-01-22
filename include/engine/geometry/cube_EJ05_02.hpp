#ifndef __CUBE_EJ05_02_H__
#define __CUBE_EJ05_02_H__ 1

#include "geometry.hpp"

class CubeWrapp final : public Geometry {
    public:
        CubeWrapp() = delete;
        explicit CubeWrapp(float size);

    private:
        float _size;
};
#endif