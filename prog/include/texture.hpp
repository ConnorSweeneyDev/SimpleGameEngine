#pragma once

#include <memory>

class Texture
{
    public:
        template <typename Type> void specify_texture(std::shared_ptr<Type>& object);

        template <typename Type> void assign_texture_to_object(std::shared_ptr<Type>& object);
};
extern Texture texture;

#include "texture.tpl.hpp"
