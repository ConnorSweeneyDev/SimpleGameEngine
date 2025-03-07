#pragma once

#include <memory>

#include "rename.hpp"

namespace cse::object
{
  template <typename Type> using Object_pointer = std::shared_ptr<Type>;

  struct Transform_data
  {
    glm::Vec3 translation = {};
    glm::Vec3 rotation = {};
    glm::Vec3 scale = {};
  };

  struct Render_data
  {
    gl::Uint vertex_array_object = 0;
    gl::Uint vertex_buffer_object = 0;
    gl::Uint index_buffer_object = 0;
    gl::Uint texture_object = 0;
    gl::Uint shader_object = 0;
  };

  struct Texture_data
  {
    enum struct Flip_direction
    {
      NONE,
      HORIZONTAL,
      VERTICAL,
      DIAGONAL
    };

    const unsigned char *source = nullptr;
    int width = 0;
    int height = 0;
    int channels = 0;
    int total_frames = 1;
    int current_frame = 1;
    Flip_direction flip_direction = Flip_direction::NONE;
  };

  struct Shader_data
  {
    const char *vertex_source = nullptr;
    const char *fragment_source = nullptr;
  };
}
