#pragma once

#include "rename.hpp"
#include <glad.h>

namespace cse::object
{
  class Shader
  {
  public:
    void specify();
    template <typename Type>
    void set_program(Object_ptr<Type> &object, const char vertex_source[],
                     const char fragment_source[]);

  private:
    gl::Uint compile(const gl::Uint type, const char *shader_source);
  };

  extern Shader shader;
}

#include "shader.tpl.hpp"
