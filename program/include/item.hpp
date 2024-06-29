#pragma once

#include <memory>
#include <vector>

#include "rename.hpp"
#include <glad.h>

namespace cse::object
{
  class Item
  {
    friend class Render;
    friend class Shader;
    friend class Texture;

  public:
    Item(const std::string i_name);

    void init(const std::vector<float> i_default_geometry);

    std::string name;

  private:
    gl::Uint vertex_array_object;
    gl::Uint vertex_buffer_object;
    gl::Uint index_buffer_object;
    gl::Uint shader_program;
    gl::Uint texture_object;
    std::string texture_path;
    int texture_width;
    int texture_height;
    int texture_channels;

    float translation_x;
    float translation_y;
    float translation_z;
    float rotation_x;
    float rotation_y;
    float rotation_z;
    float scale_x;
    float scale_y;
    float scale_z;
  };

  using Item_ptr = Object_ptr<Item>;
  using Item_ptr_list = std::vector<Item_ptr>;
  extern Item_ptr_list items;
}
