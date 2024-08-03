#pragma once

#include "rename.hpp"
#include <glm.hpp>

namespace cse::object
{
  class Camera
  {
    friend class Render;

  public:
    void update_projection_matrix();
    void update_view_matrix();

    void move_right(const float speed);
    void move_left(const float speed);
    void move_up(const float speed);
    void move_down(const float speed);
    void move_forward(const float speed);
    void move_backward(const float speed);

    void reset_transform();

    void initialize(const float fov, const float near_clip, const float far_clip,
                    const glm::Vec3 translation, const glm::Vec3 direction, const glm::Vec3 up);

  private:
    struct Camera_perspective
    {
      float fov;
      float near_clip;
      float far_clip;
    };
    Camera_perspective perspective;

    struct Camera_transform
    {
      glm::Vec3 translation;
      glm::Vec3 direction;
      glm::Vec3 up;
    };
    Camera_transform transform;
    Camera_transform initial_transform;

    struct Camera_matrix
    {
      glm::Mat4 projection;
      glm::Mat4 view;
    };
    Camera_matrix matrix;
  };

  extern Camera camera;
}
