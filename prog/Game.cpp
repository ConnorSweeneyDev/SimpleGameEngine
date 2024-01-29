#include "Game.hpp"

Game game;

void Game::InitializeGameObjects()
{
    camera.init(90.0f, 0.1f, 10.0f, glm::vec3(0.0f, 0.0f, 1.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    
    for(auto& player : players)
    {
        if (player->getName() == "Player 1")
            player->init(
                         50, 0.002,
                         defaultPlayer1Position
                        );
        else if (player->getName() == "Player 2")
            player->init(
                         200, 0.0005,
                         defaultPlayer2Position
                        );
        else
            player->init(
                         100, 0.001,
                         { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.f, 1.0f, 1.0f, 1.0f }
                        );
    }

    for(auto& item : items)
    {
        if (item->getName() == "Floor")
            item->init(defaultFloorPosition);
        else
            item->init({ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.f, 1.0f, 1.0f, 1.0f });
    }
}
