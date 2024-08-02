#include <string>
#include <vector>

#include "item.hpp"

namespace cse::object
{
  Item_ptr_list items;

  Item::Item(const std::string i_name) : name(i_name) {}

  void Item::init(const std::vector<float> i_default_geometry)
  {
    translation_x = i_default_geometry[0];
    translation_y = i_default_geometry[1];
    translation_z = i_default_geometry[2];
    rotation_x = i_default_geometry[3];
    rotation_y = i_default_geometry[4];
    rotation_z = i_default_geometry[5];
    scale_x = i_default_geometry[6];
    scale_y = i_default_geometry[7];
    scale_z = i_default_geometry[8];
  }
}
