#pragma once

#include "property.hpp"

namespace cse::object
{
  class Texture
  {
  public:
    void initialize();
    template <typename Type> void load(Object_pointer<Type> &object);

  private:
    template <typename Type> void initialize_load(Object_pointer<Type> &object);
    void cleanup_load();
  };

  inline Texture texture = {};
}

#include "texture.tpl.hpp"
