#pragma once

#include <string>
#include <vector>

#include <glad.h>

#include "object.hpp"

namespace cse::object
{
  class Item
  {
    friend class Render;
    friend class Shader;
    friend class Texture;

  public:
    Item(const std::string i_name);

    void initialize(const Transform_data &i_transform_data);

    std::string name = "";

  private:
    Transform_data transform_data = {};
    Transform_data initial_transform_data = {};

    Texture_data texture_data = {};
    Shader_data shader_data = {};
    Render_data render_data = {};
  };

  using Item_ptr = Object_ptr<Item>;
  using Item_ptr_list = std::vector<Item_ptr>;
  inline Item_ptr_list items = {};
}
