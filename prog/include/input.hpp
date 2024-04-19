#pragma once

#include "SDL_events.h"

class Input
{
    public:
        void poll_window();
        void poll_game();

    private:
        SDL_Event event;
        const Uint8* keyState = SDL_GetKeyboardState(nullptr);
};
extern Input input;
