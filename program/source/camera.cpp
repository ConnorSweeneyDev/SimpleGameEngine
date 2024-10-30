#include <memory>

#include "ext/matrix_clip_space.hpp"
#include "rename.hpp"
#include "trigonometric.hpp"

#include "camera.hpp"
#include "window.hpp"

namespace cse::object
{
  void Camera::update_projection_matrix()
  {
    float window_aspect_ratio = (float)system::window.width / (float)system::window.height;
    matrix_data.projection = glm::perspective(glm::radians(perspective_data.fov), window_aspect_ratio,
                                              perspective_data.near_clip, perspective_data.far_clip);
  }
  void Camera::update_view_matrix()
  {
    glm::Vec3 center = orientation_data.translation + orientation_data.direction;
    matrix_data.view = glm::look_at(orientation_data.translation, center, orientation_data.up);
  }

  void Camera::move_right(const float speed) { orientation_data.translation.x += speed; }
  void Camera::move_left(const float speed) { orientation_data.translation.x -= speed; }
  void Camera::move_up(const float speed) { orientation_data.translation.y += speed; }
  void Camera::move_down(const float speed) { orientation_data.translation.y -= speed; }
  void Camera::move_forward(const float speed) { orientation_data.translation.z -= speed; }
  void Camera::move_backward(const float speed) { orientation_data.translation.z += speed; }

  void Camera::reset_orientation() { orientation_data = *initial_orientation_data; }

  void Camera::initialize(const Perspective_data &i_perspective, const Orientation_data &i_orientation)
  {
    perspective_data = i_perspective;
    initial_perspective_data = std::make_unique<const Perspective_data>(perspective_data);
    orientation_data = i_orientation;
    initial_orientation_data = std::make_unique<const Orientation_data>(orientation_data);

    update_projection_matrix();
    update_view_matrix();
  }
}
