#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <glm/glm.hpp>

#include "engine/model.hpp"
#include "engine/geometry/quad.hpp"

class Player {
public:
    enum class Movement {
        Forward = 0,
        Backward = 1,
        Left = 2,
        Right = 3,
    };

    Player(Geometry hitbox, float posX, float posY, float posZ);

    void handleKeyboard(Movement direction);

    Geometry getHitbox();
    glm::vec3 getPoshitBox();

private:
    Geometry _hitbox;
    glm::vec3 _position, _posHitbox, _colorHitbox;
};
#endif