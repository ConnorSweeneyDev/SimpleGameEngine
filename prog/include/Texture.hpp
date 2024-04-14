#pragma once

#include <memory>

class Texture
{
    public:
        template <typename Type> void SpecifyTexture(std::shared_ptr<Type>& object);

        template <typename Type> void AssignTextureToObject(std::shared_ptr<Type>& object);
};
extern Texture texture;

#include "Texture.tpl.hpp"
