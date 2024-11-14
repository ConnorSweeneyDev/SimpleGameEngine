#pragma once

#include <memory>

#include "rename.hpp"

namespace cse::object
{
  class Camera
  {
    friend class Render;

  public:
    struct Perspective_data
    {
      float fov = 0.0f;
      float near_clip = 0.0f;
      float far_clip = 0.0f;
    };
    struct Orientation_data
    {
      glm::Vec3 translation = {};
      glm::Vec3 direction = {};
      glm::Vec3 up = {};
    };

  private:
    struct Matrix_data
    {
      glm::Mat4 projection = {};
      glm::Mat4 view = {};
    };

  public:
    void initialize(const Perspective_data &i_perspective, const Orientation_data &i_transform);

    void move_right(const float speed);
    void move_left(const float speed);
    void move_up(const float speed);
    void move_down(const float speed);
    void move_forward(const float speed);
    void move_backward(const float speed);
    void reset_orientation();

  private:
    void update_projection_matrix();
    void update_view_matrix();

  private:
    Perspective_data perspective_data = {};
    std::unique_ptr<const Perspective_data> initial_perspective_data = {};
    Orientation_data orientation_data = {};
    std::unique_ptr<const Orientation_data> initial_orientation_data = {};
    Matrix_data matrix_data = {};
  };

  inline Camera camera = {};
}
