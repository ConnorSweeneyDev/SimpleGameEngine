#pragma once

#include "object.hpp"

namespace cse::object
{
  class Texture
  {
  public:
    void initialize();
    template <typename Type> void load(Object_ptr<Type> &object);

  private:
    template <typename Type> void initialize_load(Object_ptr<Type> &object);
    void cleanup_load();
  };

  inline Texture texture = {};
}

#include "texture.tpl.hpp"
