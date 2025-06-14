#include "shader.hpp"

#include <cstddef>
#include <iostream>

#include "glad/glad.h"
#include "rename.hpp"

#include "item.hpp"
#include "object.hpp"
#include "player.hpp"
#include "resource.hpp"

namespace cse::object
{
  void Shader::initialize()
  {
    for (auto &player : players)
    {
      player->shader_data = Shader_data{resource::vertex_shader_source, resource::fragment_shader_source};

      update(player);
    }

    for (auto &item : items)
    {
      item->shader_data = Shader_data{resource::vertex_shader_source, resource::fragment_shader_source};

      update(item);
    }
  }

  gl::Uint Shader::compile(const gl::Uint type, const char *shader_source)
  {
    gl::Uint shader_object;

    switch (type)
    {
      case GL_VERTEX_SHADER: shader_object = gl::create_shader(GL_VERTEX_SHADER); break;
      case GL_FRAGMENT_SHADER: shader_object = gl::create_shader(GL_FRAGMENT_SHADER); break;
      default: shader_object = gl::create_shader(GL_NONE); break;
    }

    gl::shader_source(shader_object, 1, &shader_source, nullptr);
    gl::compile_shader(shader_object);

    int result;
    gl::get_shaderiv(shader_object, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
      int length;
      gl::get_shaderiv(shader_object, GL_INFO_LOG_LENGTH, &length);
      char *error_messages = new char[(size_t)length];
      gl::get_shader_info_log(shader_object, length, &length, error_messages);

      switch (type)
      {
        case GL_VERTEX_SHADER: std::cout << "GL_VERTEX_SHADER compilation failed!\n" << error_messages; break;
        case GL_FRAGMENT_SHADER: std::cout << "GL_FRAGMENT_SHADER compilation failed!\n" << error_messages; break;
        default: std::cout << "Invalid shader type!\n" << error_messages; break;
      }

      delete[] error_messages;
      gl::delete_shader(shader_object);

      return 0;
    }

    return shader_object;
  }
}
