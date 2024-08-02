#pragma once

#include <glad.h>

#include "rename.hpp"
#include "shader.hpp"

namespace cse::object
{
  template <typename Type>
  void Shader::set_program(Object_ptr<Type> &object, const char vertex_source[],
                           const char fragment_source[])
  {
    gl::Uint program_object = gl::create_program();
    gl::Uint vertex_shader = compile(GL_VERTEX_SHADER, vertex_source);
    gl::Uint fragment_shader = compile(GL_FRAGMENT_SHADER, fragment_source);

    gl::attach_shader(program_object, vertex_shader);
    gl::attach_shader(program_object, fragment_shader);
    gl::link_program(program_object);
    gl::validate_program(program_object);

    object->shader_program = program_object;
  }
}
