#pragma once

#include <memory>
#include <string>

#include "rename.hpp"

namespace cse::object
{
  template <typename Type> using Object_ptr = std::shared_ptr<Type>;

  struct Object_transform
  {
    glm::Vec3 translation = {};
    glm::Vec3 rotation = {};
    glm::Vec3 scale = {};
  };

  struct Object_data
  {
    gl::Uint vertex_array_object = 0;
    gl::Uint vertex_buffer_object = 0;
    gl::Uint index_buffer_object = 0;
    gl::Uint shader_program = 0;
    gl::Uint texture_object = 0;
    std::string texture_path = "";
    int texture_width = 0;
    int texture_height = 0;
    int texture_channels = 0;
  };
}
