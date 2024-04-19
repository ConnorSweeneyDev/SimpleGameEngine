#include "item.hpp"

ItemPtrList items;

Item::Item(std::string name) { this->name = name; }

const std::string& Item::get_name() const { return name; }

void Item::init(std::vector<float> defaultGeometry)
{
    this->translationX = defaultGeometry[0];
    this->translationY = defaultGeometry[1];
    this->translationZ = defaultGeometry[2];
    this->rotationX = defaultGeometry[3];
    this->rotationY = defaultGeometry[4];
    this->rotationZ = defaultGeometry[5];
    this->scaleX = defaultGeometry[6];
    this->scaleY = defaultGeometry[7];
    this->scaleZ = defaultGeometry[8];
}
