#pragma once

#include "Item.hpp"

class Game
{
    public:
        void InitializeGameObjects();

    private:                 
        std::vector<float> defaultPlayer1Position =
        {
            -1.5f, -0.2f, 0.0f, // Position
            0.0f, 0.0f, 0.f,    // Rotation
            1.0f, 1.0f, 1.0f    // Scale
        };
        std::vector<float> defaultPlayer2Position =
        {
            1.5f, -0.2f, 0.0f,
            0.0f, 0.0f, 0.f,
            -1.0f, 1.0f, 1.0f
        };
};
extern Game game;
