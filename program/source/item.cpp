#include <string>

#include "rename.hpp"

#include "item.hpp"

namespace cse::object
{
  Item::Item(const std::string i_name) : name(i_name) {}

  void Item::initialize(const glm::Vec3 translation, const glm::Vec3 rotation,
                        const glm::Vec3 scale)
  {
    transform.translation = translation;
    transform.rotation = rotation;
    transform.scale = scale;
    initial_transform = transform;
  }
}
