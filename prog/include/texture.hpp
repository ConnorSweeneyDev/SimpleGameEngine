#pragma once

#include <memory>

class Texture
{
    public:
        template <typename Type> void specify_textures(std::shared_ptr<Type>& object);

        template <typename Type> void load_textures(std::shared_ptr<Type>& object);
};
extern Texture texture;

#include "texture.tpl.hpp"
