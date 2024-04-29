#pragma once

#include <memory>

namespace cse
{
    class Texture
    {
        public:
            void specify();
            template <typename Type> void load(std::shared_ptr<Type>& object);

        private:
            template <typename Type> void load_init(std::shared_ptr<Type>& object);
            template <typename Type> void load_cleanup(std::shared_ptr<Type>& object);
    };
    extern Texture texture;
}

#include "texture.tpl.hpp"
