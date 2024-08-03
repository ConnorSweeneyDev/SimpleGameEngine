#pragma once

#include "rename.hpp"
#include <glad.h>

#include "object.hpp"

namespace cse::object
{
  class Shader
  {
  public:
    void initialize();
    template <typename Type>
    void set_program(Object_ptr<Type> &object, const char vertex_source[],
                     const char fragment_source[]);

  private:
    gl::Uint compile(const gl::Uint type, const char *shader_source);
  };

  inline Shader shader = {};
}

#include "shader.tpl.hpp"
