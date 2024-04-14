#include "Game.hpp"
#include "Camera.hpp"
#include "Player.hpp"
#include "Item.hpp"

Game game;

void Game::InitializeCamera()
{
    camera.init(45.0f, 0.1f, 10.0f, glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

void Game::InitializePlayers()
{
    for(auto& player : players)
    {
        if (player->getName() == "Player 1")
            player->init(50, 0.002,
                         { -1.5f, -0.2f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f });
        else if (player->getName() == "Player 2")
            player->init(200, 0.0005,
                         { 1.5f, -0.2f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f });
        else
            player->init(100, 0.001,
                         { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f });
    }
}

void Game::InitializeItems()
{
    for(auto& item : items)
    {
        if (item->getName() == "Background 1")
            item->init({ 0.0f, 1.5f, -0.45f, 0.0f, 0.0f, 0.0f, 10.0f, 5.0f, 1.0f });
        else if (item->getName() == "Background 2")
            item->init({ 0.0f, 1.5f, -0.3f, 0.0f, 0.0f, 0.0f, 10.0f, 5.0f, 1.0f });
        else if (item->getName() == "Background 3")
            item->init({ 0.0f, 1.5f, -0.15f, 0.0f, 0.0f, 0.0f, 10.0f, 5.0f, 1.0f });
        else if (item->getName() == "Shop")
            item->init({ 0.0f, 0.28f, -0.05f, 0.0f, 0.0f, 0.0f, 3.0f, 2.0f, 1.0f });
        else if (item->getName() == "Floor")
            item->init({ 0.0f, -1.2f, 0.0f, 0.0f, 0.0f, 0.0f, 10.0f, 1.0f, 1.0f });
        else
            item->init({ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f });
    }
}

void Game::objectinit()
{
    InitializeCamera();
    InitializePlayers();
    InitializeItems();
}
