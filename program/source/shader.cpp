#include <fstream>
#include <iostream>

#include "rename.hpp"
#include <glad.h>

#include "item.hpp"
#include "player.hpp"
#include "shader.hpp"

namespace cse::object
{
  Shader shader;

  void Shader::specify()
  {
    for (auto &player : players)
      set_program(player, "program/shader/vertex_shader.glsl",
                  "program/shader/fragment_shader.glsl");

    for (auto &item : items)
      set_program(item, "program/shader/vertex_shader.glsl", "program/shader/fragment_shader.glsl");
  }

  const std::string Shader::load_as_string(const std::string &shader_path)
  {
    std::string result;

    std::ifstream file(shader_path.c_str());
    std::string line;

    if (!file.is_open())
    {
      std::cout << "Unable to open file: " << shader_path << "!" << std::endl;
      return result;
    }

    while (std::getline(file, line)) result += line + "\n";

    file.close();
    return result;
  }

  gl::Uint Shader::compile(const gl::Uint type, const std::string &shader_source)
  {
    gl::Uint shader_object;

    if (type == GL_VERTEX_SHADER)
      shader_object = gl::create_shader(GL_VERTEX_SHADER);
    else if (type == GL_FRAGMENT_SHADER)
      shader_object = gl::create_shader(GL_FRAGMENT_SHADER);
    else
      shader_object = gl::create_shader(GL_NONE);

    const char *source = shader_source.c_str();
    gl::shader_source(shader_object, 1, &source, nullptr);
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

      delete[] error_messages;
      gl::delete_shader(shader_object);

      return 0;
    }

    return shader_object;
  }

  gl::Uint Shader::create_program(const std::string &vertex_shader_source,
                                  const std::string &fragment_shader_source)
  {
    gl::Uint program_object = gl::create_program();
    gl::Uint vertex_shader = compile(GL_VERTEX_SHADER, vertex_shader_source);
    gl::Uint fragment_shader = compile(GL_FRAGMENT_SHADER, fragment_shader_source);

    gl::attach_shader(program_object, vertex_shader);
    gl::attach_shader(program_object, fragment_shader);
    gl::link_program(program_object);
    gl::validate_program(program_object);

    return program_object;
  }
}
