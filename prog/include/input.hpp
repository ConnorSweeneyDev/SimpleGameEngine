#pragma once

#include "SDL_events.h"

class Input
{
    public:
        void poll_window();
        void poll_game();

        void read();

    private:
        SDL_Event event;
        const Uint8* key_state = SDL_GetKeyboardState(nullptr);
};
extern Input input;
