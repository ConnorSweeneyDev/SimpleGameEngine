#pragma once

#include <memory>
#include <string>

#include "rename.hpp"

namespace cse::object
{
  template <typename Type> using Object_ptr = std::shared_ptr<Type>;

  struct Transform_data
  {
    glm::Vec3 translation = {};
    glm::Vec3 rotation = {};
    glm::Vec3 scale = {};
  };

  struct Texture_data
  {
    std::string path = "";
    int width = 0;
    int height = 0;
    int channels = 0;
    gl::Uint object = 0;

    Texture_data &operator=(const Texture_data &other)
    {
      path = other.path;
      width = other.width;
      height = other.height;
      channels = other.channels;

      return *this;
    }
  };

  struct Shader_data
  {
    const char *vertex_source = nullptr;
    const char *fragment_source = nullptr;
    gl::Uint program = 0;

    Shader_data &operator=(const Shader_data &other)
    {
      vertex_source = other.vertex_source;
      fragment_source = other.fragment_source;

      return *this;
    }
  };

  struct Render_data
  {
    gl::Uint vertex_array_object = 0;
    gl::Uint vertex_buffer_object = 0;
    gl::Uint index_buffer_object = 0;
  };
}
