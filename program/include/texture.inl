#pragma once

#include "glad.h"
#include "rename.hpp"

#include "data.hpp"
#include "texture.hpp"

namespace cse::object
{
  template <typename Type> void Texture::load(Object_pointer<Type> &object)
  {
    initialize_load(object);

    gl::tex_image_2d(GL_TEXTURE_2D, 0, GL_RGBA, object->texture_data.width, object->texture_data.height, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, object->texture_data.source);
    if (object->name == "Player 1")
    {
      const float bottom_right[] = {0.5f, 0.0f};
      const float top_right[] = {0.5f, 1.0f};
      gl::buffer_sub_data(GL_ARRAY_BUFFER, 14 * sizeof(gl::Float), 2 * sizeof(gl::Float), &bottom_right);
      gl::buffer_sub_data(GL_ARRAY_BUFFER, 30 * sizeof(gl::Float), 2 * sizeof(gl::Float), &top_right);
    }
    if (object->name == "Player 2")
    {
      const float bottom_left[] = {0.5f, 0.0f};
      const float bottom_right[] = {0.0f, 0.0f};
      const float top_left[] = {0.5f, 1.0f};
      const float top_right[] = {0.0f, 1.0f};
      gl::buffer_sub_data(GL_ARRAY_BUFFER, 6 * sizeof(gl::Float), 2 * sizeof(gl::Float), &bottom_left);
      gl::buffer_sub_data(GL_ARRAY_BUFFER, 14 * sizeof(gl::Float), 2 * sizeof(gl::Float), &bottom_right);
      gl::buffer_sub_data(GL_ARRAY_BUFFER, 22 * sizeof(gl::Float), 2 * sizeof(gl::Float), &top_left);
      gl::buffer_sub_data(GL_ARRAY_BUFFER, 30 * sizeof(gl::Float), 2 * sizeof(gl::Float), &top_right);
    }

    cleanup_load();
  }

  template <typename Type> void Texture::initialize_load(Object_pointer<Type> &object)
  {
    gl::bind_vertex_array(object->render_data.vertex_array_object);
    gl::bind_buffer(GL_ARRAY_BUFFER, object->render_data.vertex_buffer_object);
    gl::bind_buffer(GL_ELEMENT_ARRAY_BUFFER, object->render_data.index_buffer_object);
    gl::bind_texture(GL_TEXTURE_2D, object->render_data.texture_object);
  }
}
