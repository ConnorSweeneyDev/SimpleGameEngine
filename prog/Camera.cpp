#include "Camera.hpp"

Camera camera;

glm::mat4 Camera::getViewMatrix() const { return glm::lookAt(position, position + direction, up); }

void Camera::MoveUp(float speed) { position.y += speed * util.getDeltaTime(); }       // Movements are on the global axes, since the camera cannot rotate
void Camera::MoveDown(float speed) { position.y -= speed * util.getDeltaTime(); }
void Camera::MoveLeft(float speed) { position.x -= speed * util.getDeltaTime(); }
void Camera::MoveRight(float speed) { position.x += speed * util.getDeltaTime(); }
void Camera::MoveForward(float speed) { position.z -= speed * util.getDeltaTime(); }
void Camera::MoveBackward(float speed) { position.z += speed * util.getDeltaTime(); }

void Camera::ResetPosition()
{
    position = initial[0];
    direction = initial[1];
    up = initial[2];
}

void Camera::init(glm::vec3 position, glm::vec3 direction, glm::vec3 up)
{
    initial.push_back(this->position = position);
    initial.push_back(this->direction = direction);
    initial.push_back(this->up = up);
}
