#include "rename.hpp"
#include <gtc/matrix_transform.hpp>

#include "camera.hpp"
#include "time.hpp"
#include "window.hpp"

namespace cse::object
{
  Camera camera;

  void Camera::update_projection_matrix()
  {
    float aspect_ratio = (float)system::window.width / (float)system::window.height;
    projection_matrix = glm::perspective(glm::radians(fov), aspect_ratio, near_clip, far_clip);
  }
  void Camera::update_view_matrix()
  {
    view_matrix = glm::look_at(position, position + direction, up);
  }

  void Camera::move_right(const float speed) { position.x += speed; }
  void Camera::move_left(const float speed) { position.x -= speed; }
  void Camera::move_up(const float speed) { position.y += speed; }
  void Camera::move_down(const float speed) { position.y -= speed; }
  void Camera::move_forward(const float speed) { position.z -= speed; }
  void Camera::move_backward(const float speed) { position.z += speed; }

  void Camera::reset_orientation()
  {
    position = initial_orientation[0];
    direction = initial_orientation[1];
    up = initial_orientation[2];
  }

  void Camera::init(const float i_fov, const float i_near_clip, const float i_far_clip,
                    const glm::Vec3 i_position, const glm::Vec3 i_direction, const glm::Vec3 i_up)
  {
    fov = i_fov;
    near_clip = i_near_clip;
    far_clip = i_far_clip;

    initial_orientation.push_back(position = i_position);
    initial_orientation.push_back(direction = i_direction);
    initial_orientation.push_back(up = i_up);

    update_projection_matrix();
    update_view_matrix();
  }
}
