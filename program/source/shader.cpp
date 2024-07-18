#include <fstream>
#include <iostream>

#include "rename.hpp"
#include <glad.h>

#include "item.hpp"
#include "player.hpp"
#include "resource.hpp"
#include "shader.hpp"

namespace cse::object
{
  Shader shader;

  void Shader::specify()
  {
    for (auto &player : players)
      set_program(player, vertex_shader_resource, fragment_shader_resource);

    for (auto &item : items) set_program(item, vertex_shader_resource, fragment_shader_resource);
  }

  gl::Uint Shader::compile(const gl::Uint type, const char *shader_source)
  {
    gl::Uint shader_object;

    if (type == GL_VERTEX_SHADER)
      shader_object = gl::create_shader(GL_VERTEX_SHADER);
    else if (type == GL_FRAGMENT_SHADER)
      shader_object = gl::create_shader(GL_FRAGMENT_SHADER);
    else
      shader_object = gl::create_shader(GL_NONE);

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

      if (type == GL_VERTEX_SHADER)
        std::cout << "GL_VERTEX_SHADER compilation failed!\n" << error_messages;
      else if (type == GL_FRAGMENT_SHADER)
        std::cout << "GL_FRAGMENT_SHADER compilation failed!\n" << error_messages;
      else
        std::cout << "Invalid shader type!\n" << error_messages;

      delete[] error_messages;
      gl::delete_shader(shader_object);

      return 0;
    }

    return shader_object;
  }
}
