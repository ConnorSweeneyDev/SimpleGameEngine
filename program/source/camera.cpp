#include "rename.hpp"
#include <ext/matrix_clip_space.hpp>
#include <trigonometric.hpp>

#include "camera.hpp"
#include "window.hpp"

namespace cse::object
{
  Camera camera;

  void Camera::update_projection_matrix()
  {
    float window_aspect_ratio = (float)system::window.width / (float)system::window.height;
    matrix.projection = glm::perspective(glm::radians(perspective.fov), window_aspect_ratio,
                                         perspective.near_clip, perspective.far_clip);
  }
  void Camera::update_view_matrix()
  {
    matrix.view = glm::look_at(transform.translation, transform.translation + transform.direction,
                               transform.up);
  }

  void Camera::move_right(const float speed) { transform.translation.x += speed; }
  void Camera::move_left(const float speed) { transform.translation.x -= speed; }
  void Camera::move_up(const float speed) { transform.translation.y += speed; }
  void Camera::move_down(const float speed) { transform.translation.y -= speed; }
  void Camera::move_forward(const float speed) { transform.translation.z -= speed; }
  void Camera::move_backward(const float speed) { transform.translation.z += speed; }

  void Camera::reset_transform() { transform = initial_transform; }

  void Camera::init(const float fov, const float near_clip, const float far_clip,
                    const glm::Vec3 translation, const glm::Vec3 direction, const glm::Vec3 up)
  {
    perspective.fov = fov;
    perspective.near_clip = near_clip;
    perspective.far_clip = far_clip;

    transform.translation = translation;
    transform.direction = direction;
    transform.up = up;
    initial_transform = transform;

    update_projection_matrix();
    update_view_matrix();
  }
}
