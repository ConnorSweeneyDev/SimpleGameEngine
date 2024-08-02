#pragma once

#include <memory>
#include <string>

#include "rename.hpp"

namespace cse::object
{
  template <typename Type> using Object_ptr = std::shared_ptr<Type>;

  struct Object_transform
  {
    glm::Vec3 translation;
    glm::Vec3 rotation;
    glm::Vec3 scale;
  };

  struct Object_data
  {
    gl::Uint vertex_array_object;
    gl::Uint vertex_buffer_object;
    gl::Uint index_buffer_object;
    gl::Uint shader_program;
    gl::Uint texture_object;
    std::string texture_path;
    int texture_width;
    int texture_height;
    int texture_channels;
  };
}
