#include <glm/glm.hpp>

#include "engine/player.hpp"
#include "engine/model.hpp"
#include "engine/player.hpp"

Player::Player(const Model& pj, float posX, float posY, float posZ, uint16_t lifes)
	: _pj(pj), _position(glm::vec3(posX, posY, posZ)), _lifes(lifes) {
}

void Player::handleKeyboard(Movement direction, float dt) {
    const float velocity = k_Speed * dt;

    switch (direction) {
    case Movement::Forward: _position += velocity; break;
    case Movement::Backward: _position -= velocity; break;
    case Movement::Left: _position -= velocity; break;
    case Movement::Right: _position += velocity; break;
    default:;
    }
}

void Player::updateLifes(int mode, uint16_t hits)
{
    if (mode = 0) {//Consigue una vida
        _lifes += hits;
    }
    else {//Pierde una vida
        _lifes -= hits;
    }
}

void Player::updateScore(uint32_t points)
{
    _score += points;
}
