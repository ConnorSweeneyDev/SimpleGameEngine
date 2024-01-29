#pragma once

#include "Player.hpp"
#include "Render.hpp"

class Input
{
    public:
        void PollWindow();
        void PollGame();

    private:
        SDL_Event event;
        const Uint8* keyState = SDL_GetKeyboardState(nullptr);
        
        std::shared_ptr<Player> player1;
        std::shared_ptr<Player> player2;
};
extern Input input;
