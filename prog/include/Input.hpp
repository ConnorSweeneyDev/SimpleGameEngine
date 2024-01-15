#pragma once

#include "Player.hpp"

class Input
{
    public:
        void PollWindow();
        void PollGame();

    private:
        SDL_Event event;
        const Uint8* keyState = SDL_GetKeyboardState(nullptr);
};
extern Input input;
