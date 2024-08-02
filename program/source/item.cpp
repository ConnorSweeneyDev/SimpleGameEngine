#include <string>
#include <vector>

#include "item.hpp"

namespace cse::object
{
  Item_ptr_list items;

  Item::Item(const std::string i_name) : name(i_name) {}

  void Item::init(const std::vector<float> default_geometry)
  {
    transform.initial.push_back(transform.translation_x = default_geometry[0]);
    transform.initial.push_back(transform.translation_y = default_geometry[1]);
    transform.initial.push_back(transform.translation_z = default_geometry[2]);
    transform.initial.push_back(transform.rotation_x = default_geometry[3]);
    transform.initial.push_back(transform.rotation_y = default_geometry[4]);
    transform.initial.push_back(transform.rotation_z = default_geometry[5]);
    transform.initial.push_back(transform.scale_x = default_geometry[6]);
    transform.initial.push_back(transform.scale_y = default_geometry[7]);
    transform.initial.push_back(transform.scale_z = default_geometry[8]);
  }
}
