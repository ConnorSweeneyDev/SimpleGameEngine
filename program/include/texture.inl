#pragma once

#include "glad.h"
#include "rename.hpp"

#include "data.hpp"
#include "texture.hpp"

namespace cse::object
{
  template <typename Type> void Texture::update(Object_pointer<Type> &object)
  {
    initialize_buffers(object);

    update_frame(object);
    flip_frame(object->texture_data.flip_direction);

    cleanup_buffers();
  }

  template <typename Type> void Texture::initialize_buffers(Object_pointer<Type> &object)
  {
    gl::bind_vertex_array(object->render_data.vertex_array_object);
    gl::bind_buffer(GL_ARRAY_BUFFER, object->render_data.vertex_buffer_object);
    gl::bind_buffer(GL_ELEMENT_ARRAY_BUFFER, object->render_data.index_buffer_object);
    gl::bind_texture(GL_TEXTURE_2D, object->render_data.texture_object);
  }

  template <typename Type> void Texture::update_frame(Object_pointer<Type> &object)
  {
    gl::tex_image_2d(GL_TEXTURE_2D, 0, GL_RGBA, object->texture_data.width, object->texture_data.height, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, object->texture_data.source);
    const float section_width = 1.0f / (float)object->texture_data.total_frames;
    const float bottom_left[] = {((float)object->texture_data.current_frame - 1.0f) * section_width, 0.0f};
    const float bottom_right[] = {bottom_left[0] + section_width, 0.0f};
    const float top_left[] = {((float)object->texture_data.current_frame - 1.0f) * section_width, 1.0f};
    const float top_right[] = {top_left[0] + section_width, 1.0f};
    gl::buffer_sub_data(GL_ARRAY_BUFFER, 6 * sizeof(gl::Float), 2 * sizeof(gl::Float), &bottom_left);
    gl::buffer_sub_data(GL_ARRAY_BUFFER, 14 * sizeof(gl::Float), 2 * sizeof(gl::Float), &bottom_right);
    gl::buffer_sub_data(GL_ARRAY_BUFFER, 22 * sizeof(gl::Float), 2 * sizeof(gl::Float), &top_left);
    gl::buffer_sub_data(GL_ARRAY_BUFFER, 30 * sizeof(gl::Float), 2 * sizeof(gl::Float), &top_right);
  }
}
