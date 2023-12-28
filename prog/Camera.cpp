#include "Camera.hpp"

Camera::Camera()
{
    cPosition = glm::vec3(0.0f, 0.0f, 3.0f);
    cDirection = glm::vec3(0.0f, 0.0f, -1.0f);
    cUp = glm::vec3(0.0f, 1.0f, 0.0f);
}

glm::mat4 Camera::getViewMatrix() const
{
    return glm::lookAt(cPosition, cPosition + cDirection, cUp);
}

void Camera::moveForward(float speed)
{
    cPosition.z -= speed;
}
void Camera::moveBackward(float speed)
{
    cPosition.z += speed;
}
void Camera::moveUp(float speed)
{
    cPosition.y += speed;
}
void Camera::moveDown(float speed)
{
    cPosition.y -= speed;
}
void Camera::moveLeft(float speed)
{
    cPosition.x -= speed;
}
void Camera::moveRight(float speed)
{
    cPosition.x += speed;
}
