#ifndef __QUAD_H__
#define __QUAD_H__ 1

#include "geometry.hpp"

class Quad final: public Geometry {
    public:
        Quad() = delete;
        Quad(float size);
        Quad(float size, int8_t mode);

    private:
        float _size;
};
#endif