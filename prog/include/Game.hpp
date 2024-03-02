#pragma once

#include "Item.hpp"
#include "Render.hpp"

class Game
{
    public:
        void InitializeCamera();
        void InitializePlayers();
        void InitializeItems();

        void objectinit();
};
extern Game game;
