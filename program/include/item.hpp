#pragma once

#include <memory>
#include <string>
#include <vector>

#include "data.hpp"

namespace cse::object
{
  class Item
  {
    friend class Render;
    friend class Shader;
    friend class Texture;

  public:
    Item(const std::string &i_name);

    void initialize(const Transform_data &i_transform_data);

    std::string name = "";

  private:
    Render_data render_data = {};
    Transform_data transform_data = {};
    std::unique_ptr<const Transform_data> initial_transform_data = {};
    Texture_data texture_data = {};
    Shader_data shader_data = {};
  };

  using Item_pointer = Object_pointer<Item>;
  using Item_pointer_list = std::vector<Item_pointer>;
  inline Item_pointer_list items = {};
}
