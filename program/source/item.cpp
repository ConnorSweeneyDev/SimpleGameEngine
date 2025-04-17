#include "item.hpp"

#include <memory>
#include <string>

#include "object.hpp"

namespace cse::object
{
  Item::Item(const std::string &i_name) : name(i_name) {}

  void Item::initialize(const Transform_data &i_transform_data)
  {
    transform_data = i_transform_data;
    initial_transform_data = std::make_unique<const Transform_data>(transform_data);
  }
}
