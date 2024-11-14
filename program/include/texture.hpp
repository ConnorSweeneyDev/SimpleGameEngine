#pragma once

#include "data.hpp"

namespace cse::object
{
  class Texture
  {
  public:
    void initialize();
    template <typename Type> void update(Object_pointer<Type> &object);

  private:
    template <typename Type> void initialize_buffers(Object_pointer<Type> &object);

    template <typename Type> void update_frame(Object_pointer<Type> &object);
    void flip_frame(const Texture_data::Flip_direction direction);

    void cleanup_buffers();
  };

  inline Texture texture = {};
}

#include "texture.inl"
