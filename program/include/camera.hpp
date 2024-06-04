#pragma once

#include <vector>

#include "rename.hpp"
#include <glm.hpp>

namespace cse::object
{
  class Camera
  {
  public:
    void update_projection_matrix();
    void update_view_matrix();

    void move_right(const float speed);
    void move_left(const float speed);
    void move_up(const float speed);
    void move_down(const float speed);
    void move_forward(const float speed);
    void move_backward(const float speed);

    void reset_orientation();

    void init(const float i_fov, const float i_near_clip, const float i_far_clip,
              const glm::Vec3 i_position, const glm::Vec3 i_direction, const glm::Vec3 i_up);

    glm::Mat4 projection_matrix;
    glm::Mat4 view_matrix;

  private:
    float fov;
    float near_clip;
    float far_clip;
    glm::Vec3 position;
    glm::Vec3 direction;
    glm::Vec3 up;

    std::vector<glm::Vec3> initial_orientation;
  };

  extern Camera camera;
}
