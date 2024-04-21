#include "item.hpp"

namespace cse
{
    Item_ptr_list items;

    Item::Item(std::string name) { this->name = name; }

    const std::string& Item::get_name() const { return name; }

    void Item::init(std::vector<float> default_geometry)
    {
        this->translation_x = default_geometry[0];
        this->translation_y = default_geometry[1];
        this->translation_z = default_geometry[2];
        this->rotation_x = default_geometry[3];
        this->rotation_y = default_geometry[4];
        this->rotation_z = default_geometry[5];
        this->scale_x = default_geometry[6];
        this->scale_y = default_geometry[7];
        this->scale_z = default_geometry[8];
    }
}
