#include <glm/glm.hpp>

#include "engine/player.hpp"
#include "engine/model.hpp"
#include "engine/player.hpp"

#include <iostream>

//Player::Player(Geometry hitbox, float posX, float posY, float posZ)
Player::Player(glm::vec3 pos)
	//: _hitbox(hitbox), _position(glm::vec3(posX, posY, posZ)) {
    : _position(pos) {
    _colorHitbox = glm::vec3(1.0f, 1.0f, 1.0f);
    _vertical = glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f));
    _horizontal = glm::normalize(glm::vec3(0.0f, 0.0f, 1.0f));
}

void Player::handleKeyboard(Movement direction, float dt) {
    std::cout << "AntX:" << _position.x << std::endl;
    switch (direction) {
    //case Movement::Forward: _position += glm::vec3(0.1f * dt, 0.0f, 0.0f); break;
    case Movement::Forward: _position += _vertical * dt; 
        std::cout << "V:" << _vertical.x << std::endl;
        std::cout << "Dt:" << dt << std::endl;
        std::cout << "PostX:" << _position.x << std::endl;break;
    //case Movement::Backward: _position -= glm::vec3(-0.1f * dt, 0.0f, 0.0f); break;
    case Movement::Backward: _position -= _vertical * dt; break;
    //case Movement::Left: _position -= glm::vec3(0.0f, 0.0f, 0.1f * dt); break;
    case Movement::Left: _position -= _horizontal * dt; break;
    //case Movement::Right: _position += glm::vec3(0.0f, 0.0f, -0.1f * dt); break;
    case Movement::Right: _position += _horizontal * dt; break;
    default:;
    }
}

void Player::setHitbox(Geometry hitbox) {
    _hitbox = hitbox;
}

Geometry Player::getHitbox() {
    return _hitbox;
}

glm::vec3 Player::getPoshitBox(){
    return _position;
}
