#include "Camera.hpp"

Camera camera;

glm::mat4 Camera::getViewMatrix() const { return glm::lookAt(position, position + direction, up); }

void Camera::MoveUp(float speed) { position.y += speed; }       // Movements are on the global axes, since the camera cannot rotate
void Camera::MoveDown(float speed) { position.y -= speed; }
void Camera::MoveLeft(float speed) { position.x -= speed; }
void Camera::MoveRight(float speed) { position.x += speed; }
void Camera::MoveForward(float speed) { position.z -= speed; }
void Camera::MoveBackward(float speed) { position.z += speed; }

void Camera::ResetPosition()
{
    position = glm::vec3(0.0f, 0.0f, 3.0f);
    direction = glm::vec3(0.0f, 0.0f, -1.0f);
    up = glm::vec3(0.0f, 1.0f, 0.0f);
}

void Camera::init()
{
    position = glm::vec3(0.0f, 0.0f, 3.0f);
    direction = glm::vec3(0.0f, 0.0f, -1.0f);
    up = glm::vec3(0.0f, 1.0f, 0.0f);
}
