#pragma once

#include "rename.hpp"
#include <glad.h>

#include "object.hpp"
#include "shader.hpp"

namespace cse::object
{
  template <typename Type> void Shader::load(Object_pointer<Type> &object)
  {
    gl::Uint shader_object = gl::create_program();
    gl::Uint vertex_shader = compile(GL_VERTEX_SHADER, object->shader_data.vertex_source);
    gl::Uint fragment_shader = compile(GL_FRAGMENT_SHADER, object->shader_data.fragment_source);

    gl::attach_shader(shader_object, vertex_shader);
    gl::attach_shader(shader_object, fragment_shader);
    gl::link_program(shader_object);
    gl::validate_program(shader_object);

    object->render_data.shader_object = shader_object;
  }
}
