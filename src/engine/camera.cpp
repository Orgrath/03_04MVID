#include "engine/camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(const glm::vec3& position, const glm::vec3& up, float yaw, float pitch)
 : _position(position), _worldUp(up), _yaw(yaw), _pitch(pitch), _fov(k_FOV) {
    updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
    : _position(glm::vec3(posX, posY, posZ)), _worldUp(glm::vec3(upX, upY, upZ)), _yaw(yaw), _pitch(pitch), _fov(k_FOV) {
    updateCameraVectors();
}


glm::mat4 Camera::getViewMatrix() const {

    return glm::lookAt(_position, _position + _front, _up);
}

glm::mat4 Camera::getViewMatrix_EJ06_02() const {

    glm::vec3 camDir = glm::normalize(_position - (_position + _front));

    glm::vec3 camRight = glm::normalize(glm::cross(_up, camDir));
    glm::vec3 camUp = glm::normalize(glm::cross(camDir, camRight));
    
    glm::mat4 view = { camRight.x, camUp.x , camDir.x, 0.0f,
                        camRight.y, camUp.y, camDir.y, 0.0f,
                        camRight.z, camUp.z, camDir.z, 0.0f,
                        0.0f, 0.0f, 0.0f, 1.0f };

    glm::mat4 pos = { 1.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 1.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 1.0f, 0.0f,
                    - _position.x, - _position.y, - _position.z, 1.0f };

    return view * pos;
}

float Camera::getFOV() const {
    return _fov;
}

glm::vec3 Camera::getPosition() const {
    return _position;
}

glm::vec3 Camera::getForward() const {
    return _front;
}

void Camera::updateCameraVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    front.y = sin(glm::radians(_pitch));
    front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    _front = glm::normalize(front);

    _right = glm::normalize(glm::cross(_front, _worldUp));
    _up = glm::normalize(glm::cross(_right, _front));
}

void Camera::handleKeyboard(Movement direction, float dt) {
    const float velocity = k_Speed * dt;

    switch (direction) {
        case Movement::Forward: _position += _front * velocity; break;
        case Movement::Backward: _position -= _front * velocity; break;
        case Movement::Left: _position -= _right * velocity; break;
        case Movement::Right: _position += _right * velocity; break;
        case Movement::Up: _position += _up * velocity; break;
        case Movement::Down: _position -= _up * velocity; break;
        default:;
    }
}

void Camera::handleKeyboard_EJ06_01(Movement direction, float dt) {
    const float velocity = k_Speed_EJ06_01 * dt;

    switch (direction) {
    case Movement::Forward: _position += glm::vec3{ _front.x, 0.0f, _front.z } * velocity; break;
    case Movement::Backward: _position -= glm::vec3{ _front.x, 0.0f, _front.z } * velocity; break;
    case Movement::Left: _position -= _right * velocity; break;
    case Movement::Right: _position += _right * velocity; break;
    default:;
    }
}

void Camera::handleMouseMovement(float xoffset, float yoffset, bool constrainPitch) {
    const float xoff = xoffset * k_Sensitivity;
    const float yoff = yoffset * k_Sensitivity;

    _yaw += xoff;
    _pitch += yoff;

    if (constrainPitch) {
        if (_pitch > 89.0f) _pitch = 89.0f;
        if (_pitch < -89.0f) _pitch = -89.0f;
    }

    updateCameraVectors();
}

void Camera::handleMouseScroll(float yoffset) {
    if (_fov >= 1.0f && _fov <= 45.0f) _fov -= yoffset;
    if (_fov <= 1.0f) _fov = 1.0f;
    if (_fov >= 45.0f) _fov = 45.0f;
}

void directionCamera(float xoffset, float yoffset) {
    _yaw += xoffset;
    _pitch += yoffset;

    updateCameraVectors();
}

