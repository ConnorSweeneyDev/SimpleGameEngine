#pragma once

#include <memory>

#include "rename.hpp"

namespace cse::object
{
  template <typename Type> using Object_pointer = std::shared_ptr<Type>;

  struct Render_data
  {
    gl::Uint vertex_array_object = 0;
    gl::Uint vertex_buffer_object = 0;
    gl::Uint index_buffer_object = 0;
    gl::Uint texture_object = 0;
    gl::Uint shader_object = 0;
  };
  struct Transform_data
  {
    glm::Vec3 translation = {};
    glm::Vec3 rotation = {};
    glm::Vec3 scale = {};
  };
  struct Texture_data
  {
    int width = 0;
    int height = 0;
    int channels = 0;
    const unsigned char *data = nullptr;
  };
  struct Shader_data
  {
    const char *vertex_source = nullptr;
    const char *fragment_source = nullptr;
  };
}
