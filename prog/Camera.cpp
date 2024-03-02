#include "Camera.hpp"

Camera camera;

const glm::mat4& Camera::getProjectionMatrix() const { return projectionMatrix; }
const glm::mat4& Camera::getViewMatrix() const { return viewMatrix; }

void Camera::UpdateProjectionMatrix() { projectionMatrix = glm::perspective(glm::radians(fov), (float)window.getWidth() / (float)window.getHeight(), nearClip, farClip); }
void Camera::UpdateViewMatrix() { viewMatrix = glm::lookAt(position, position + direction, up); }

// Camera movement is on the global coordinate system
void Camera::MoveUp(float speed) { position.y += speed * time_util.getDeltaTime(); }
void Camera::MoveDown(float speed) { position.y -= speed * time_util.getDeltaTime(); }
void Camera::MoveLeft(float speed) { position.x -= speed * time_util.getDeltaTime(); }
void Camera::MoveRight(float speed) { position.x += speed * time_util.getDeltaTime(); }
void Camera::MoveForward(float speed) { position.z -= speed * time_util.getDeltaTime(); }
void Camera::MoveBackward(float speed) { position.z += speed * time_util.getDeltaTime(); }

// Camera rotation is relative to itself
void Camera::RotateXPos(float speed) { direction = glm::rotate(direction, speed * time_util.getDeltaTime(),  glm::cross(direction, up)); }
void Camera::RotateXNeg(float speed) { direction = glm::rotate(direction, -speed * time_util.getDeltaTime(), glm::cross(direction, up)); }
void Camera::RotateYPos(float speed) { direction = glm::rotate(direction, speed * time_util.getDeltaTime(), up); }
void Camera::RotateYNeg(float speed) { direction = glm::rotate(direction, -speed * time_util.getDeltaTime(), up); }
void Camera::RotateZPos(float speed) { up = glm::vec3(glm::rotate(glm::mat4(1.0f), speed * time_util.getDeltaTime(), direction) * glm::vec4(up, 1.0f)); }
void Camera::RotateZNeg(float speed) { up = glm::vec3(glm::rotate(glm::mat4(1.0f), -speed * time_util.getDeltaTime(), direction) * glm::vec4(up, 1.0f)); }

void Camera::ResetPosition()
{
    position = initialPosition[0];
    direction = initialPosition[1];
    up = initialPosition[2];
}

void Camera::init(float fov, float nearClip, float farClip, glm::vec3 position, glm::vec3 direction, glm::vec3 up)
{
    this->fov = fov;
    this->nearClip = nearClip;
    this->farClip = farClip;

    initialPosition.push_back(this->position = position);
    initialPosition.push_back(this->direction = direction);
    initialPosition.push_back(this->up = up);

    UpdateProjectionMatrix();
    UpdateViewMatrix();
}
