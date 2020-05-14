#ifndef __VISOR_H__
#define __VISOR_H__ 1

#include "geometry.hpp"

class Visor final: public Geometry {
    public:
        Visor() = delete;
        explicit Visor(float position);

    private:
        float _position;
};
#endif