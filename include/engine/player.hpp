#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <glm/glm.hpp>

#include "engine/model.hpp"
#include "engine/geometry/cube.hpp"

const float k_Speed = 1.0f;
uint32_t score = 0;

class Player {
public:
    enum class Movement {
        Forward = 0,
        Backward = 1,
        Left = 2,
        Right = 3,
    };

    Player(const Model& pj, Cube hitbox, float posX, float posY, float posZ, uint16_t lifes);

    void handleKeyboard(Movement direction, float dt);
    void updateLifes(int mode, uint16_t hits);
    void updateScore(uint32_t points);

    //Provisional
    Geometry getHitbox();

private:
    Model _pj;
    Cube _hitbox;
    glm::vec3 _position;
    uint16_t _lifes;
    uint32_t _score;
};

#endif