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

    void init(const std::vector<float> default_geometry);

    std::string name;

  private:
    Object_transform transform;
    Object_data data;
  };

  using Item_ptr = Object_ptr<Item>;
  using Item_ptr_list = std::vector<Item_ptr>;
  extern Item_ptr_list items;
}
