#include <glm/glm.hpp>

#include "engine/player.hpp"
#include "engine/model.hpp"
#include "engine/player.hpp"

Player::Player(Geometry hitbox, float posX, float posY, float posZ)
	: _hitbox(hitbox), _position(glm::vec3(posX, posY, posZ)) {
    _colorHitbox = glm::vec3(1.0f, 1.0f, 1.0f);
}

void Player::handleKeyboard(Movement direction) {

    switch (direction) {
    case Movement::Forward: _position += glm::vec3(0.1f, 0.0f, 0.0f); break;
    case Movement::Backward: _position -= glm::vec3(-0.1f, 0.0f, 0.0f); break;
    case Movement::Left: _position -= glm::vec3(0.0f, 0.0f, 0.1f); break;
    case Movement::Right: _position += glm::vec3(0.0f, 0.0f, -0.1f); break;
    default:;
    }
}

Geometry Player::getHitbox() {
    return _hitbox;
}

glm::vec3 Player::getPoshitBox(){
    return _position;
}
