#pragma once

#include "rename.hpp"

namespace cse::object
{
  class Texture
  {
  public:
    void specify();
    template <typename Type> void load(Object_ptr<Type> &object);

  private:
    template <typename Type> void load_init(Object_ptr<Type> &object);
    void load_cleanup();
  };

  extern Texture texture;
}

#include "texture.tpl.hpp" // IWYU pragma: keep
