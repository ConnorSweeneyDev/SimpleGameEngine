#pragma once

#include <memory>

namespace cse
{
    class Texture
    {
        public:
            void specify_textures();

            template <typename Type> void load_texture(std::shared_ptr<Type>& object);

            template <typename Type> void texture_load_init(std::shared_ptr<Type>& object);
            template <typename Type> void texture_load_cleanup(std::shared_ptr<Type>& object);
    };
    extern Texture texture;
}

#include "texture.tpl.hpp"
