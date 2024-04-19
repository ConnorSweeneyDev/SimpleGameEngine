#include <glm/gtc/matrix_transform.hpp>

#include "camera.hpp"
#include "window.hpp"
#include "time_util.hpp"

Camera camera;

const glm::mat4& Camera::get_projection_matrix() const { return projectionMatrix; }
const glm::mat4& Camera::get_view_matrix() const { return viewMatrix; }

void Camera::update_projection_matrix() { projectionMatrix = glm::perspective(glm::radians(fov), (float)window.get_width() / (float)window.get_height(), nearClip, farClip); }
void Camera::update_view_matrix() { viewMatrix = glm::lookAt(position, position + direction, up); }

// Camera movement is on the global coordinate system
void Camera::move_right(float speed) { position.x += speed * time_util.get_delta_time(); }
void Camera::move_left(float speed) { position.x -= speed * time_util.get_delta_time(); }
void Camera::move_up(float speed) { position.y += speed * time_util.get_delta_time(); }
void Camera::move_down(float speed) { position.y -= speed * time_util.get_delta_time(); }
void Camera::move_forward(float speed) { position.z -= speed * time_util.get_delta_time(); }
void Camera::move_backward(float speed) { position.z += speed * time_util.get_delta_time(); }

void Camera::reset_position()
{
    position = initialOrientation[0];
    direction = initialOrientation[1];
    up = initialOrientation[2];
}

void Camera::init(float fov, float nearClip, float farClip, glm::vec3 position, glm::vec3 direction, glm::vec3 up)
{
    this->fov = fov;
    this->nearClip = nearClip;
    this->farClip = farClip;

    initialOrientation.push_back(this->position = position);
    initialOrientation.push_back(this->direction = direction);
    initialOrientation.push_back(this->up = up);

    update_projection_matrix();
    update_view_matrix();
}
