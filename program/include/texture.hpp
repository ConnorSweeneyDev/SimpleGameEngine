#pragma once

#include "object.hpp"

namespace cse::object
{
  class Texture
  {
  public:
    void specify_all();
    template <typename Type> void load(Object_ptr<Type> &object);

  private:
    template <typename Type> void load_init(Object_ptr<Type> &object);
    void load_cleanup();
  };

  extern Texture texture;
}

#include "texture.tpl.hpp"
