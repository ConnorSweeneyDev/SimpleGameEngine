#pragma once

#include <memory>

namespace cse::object
{
    class Texture
    {
        public:
            void specify();
            template <typename Type> void load(std::shared_ptr<Type>& object);

        private:
            template <typename Type> void load_init(std::shared_ptr<Type>& object);
            void load_cleanup();
    };
    extern Texture texture;
}

#include "texture.tpl.hpp"
