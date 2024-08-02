#pragma once

#include <memory>
#include <string>
#include <vector>

#include "rename.hpp"

namespace cse::object
{
  template <typename Type> using Object_ptr = std::shared_ptr<Type>;

  struct Object_transform
  {
    float translation_x;
    float translation_y;
    float translation_z;
    float rotation_x;
    float rotation_y;
    float rotation_z;
    float scale_x;
    float scale_y;
    float scale_z;
    std::vector<float> initial;
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
