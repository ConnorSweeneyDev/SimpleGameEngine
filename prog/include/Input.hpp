#pragma once

#include "GameObject.hpp"

class Input
{
    public:
        void PollEvents();
        void PollKeys();

    private:
        SDL_Event event;
        const Uint8* keyState = SDL_GetKeyboardState(nullptr);
};
extern Input input;
