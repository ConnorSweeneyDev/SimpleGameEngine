#include "Item.hpp"

ItemList items;

Item::Item(std::string name) { this->name = name; }

const std::string& Item::getName() const { return name; }

void Item::init(std::vector<float> defaultPosition)
{
    this->translationX = defaultPosition[0];
    this->translationY = defaultPosition[1];
    this->translationZ = defaultPosition[2];
    this->rotationX = defaultPosition[3];
    this->rotationY = defaultPosition[4];
    this->rotationZ = defaultPosition[5];
    this->scaleX = defaultPosition[6];
    this->scaleY = defaultPosition[7];
    this->scaleZ = defaultPosition[8];
}

ItemPtr getItemByName(const std::string& name)
{
    for (auto& item : items)
    {
        if (item->getName() == name)
        {
            return item;
        }
    }
    return nullptr;
}
