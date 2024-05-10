#include <glm/gtc/matrix_transform.hpp>

#include "camera.hpp"
#include "window.hpp"
#include "time.hpp"

namespace cse::object
{
    Camera camera;

    void Camera::update_projection_matrix()
    {
        projection_matrix = glm::perspective(glm::radians(fov),
                                            (float)platform::window.width / (float)platform::window.height,
                                            near_clip, far_clip);
    }
    void Camera::update_view_matrix() { view_matrix = glm::lookAt(position, position + direction, up); }

    void Camera::move_right(float speed) { position.x += speed * time::delta_time; }
    void Camera::move_left(float speed) { position.x -= speed * time::delta_time; }
    void Camera::move_up(float speed) { position.y += speed * time::delta_time; }
    void Camera::move_down(float speed) { position.y -= speed * time::delta_time; }
    void Camera::move_forward(float speed) { position.z -= speed * time::delta_time; }
    void Camera::move_backward(float speed) { position.z += speed * time::delta_time; }

    void Camera::reset_orientation()
    {
        position = initial_orientation[0];
        direction = initial_orientation[1];
        up = initial_orientation[2];
    }

    void Camera::init(float fov, float near_clip, float far_clip, glm::vec3 position, glm::vec3 direction, glm::vec3 up)
    {
        this->fov = fov;
        this->near_clip = near_clip;
        this->far_clip = far_clip;

        initial_orientation.push_back(this->position = position);
        initial_orientation.push_back(this->direction = direction);
        initial_orientation.push_back(this->up = up);

        update_projection_matrix();
        update_view_matrix();
    }
}