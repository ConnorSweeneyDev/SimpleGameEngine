#pragma once

#include <SDL2/SDL.h>

#include "GameObject.hpp"

class Input
{
    public:
        void pollEvents();
        void pollKeys();

    private:
        SDL_Event event;
        const Uint8* keyState = SDL_GetKeyboardState(nullptr);
};
extern Input input;
