#include <glm/glm.hpp>

#include "engine/player.hpp"
#include "engine/model.hpp"
#include "engine/player.hpp"

Player::Player(const Model& pj, Cube hitbox, float posX, float posY, float posZ, uint16_t lifes)
	: _pj(pj), _hitbox(hitbox), _position(glm::vec3(posX, posY, posZ)), _lifes(lifes) {
}

void Player::handleKeyboard(Movement direction, float dt) {
    const float velocity = k_Speed * dt;

    switch (direction) {
    case Movement::Forward: _position += glm::vec3(velocity, 0.0f, 0.0f); break;
    case Movement::Backward: _position -= glm::vec3(velocity, 0.0f, 0.0f); break;
    case Movement::Left: _position -= glm::vec3(0.0f, 0.0f, velocity); break;
    case Movement::Right: _position += glm::vec3(0.0f, 0.0f, velocity); break;
    default:;
    }
}

//Provisional
Geometry Player::getHitbox() {
    Cube hitBox = _hitbox;
    return hitBox;
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
