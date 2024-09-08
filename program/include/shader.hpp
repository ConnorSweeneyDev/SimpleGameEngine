#pragma once

#include "rename.hpp"
#include <glad.h>

#include "property.hpp"

namespace cse::object
{
  class Shader
  {
  public:
    void initialize();
    template <typename Type> void load(Object_pointer<Type> &object);

  private:
    gl::Uint compile(const gl::Uint type, const char *shader_source);
  };

  inline Shader shader = {};
}

#include "shader.tpl.hpp"
