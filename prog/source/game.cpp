#include "game.hpp"
#include "camera.hpp"
#include "player.hpp"
#include "item.hpp"

Game game;

void Game::initialize_camera()
{
    camera.init(45.0f, 0.1f, 10.0f, glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

void Game::initialize_players()
{
    for(auto& player : players)
    {
        if (player->get_name() == "Player 1")
            player->init(50, 0.002,
                         { -1.5f, -0.2f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f });
        else if (player->get_name() == "Player 2")
            player->init(200, 0.0005,
                         { 1.5f, -0.2f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f });
        else
            player->init(100, 0.001,
                         { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f });
    }
}

void Game::initialize_items()
{
    for(auto& item : items)
    {
        if (item->get_name() == "Background 1")
            item->init({ 0.0f, 1.5f, -0.45f, 0.0f, 0.0f, 0.0f, 10.0f, 5.0f, 1.0f });
        else if (item->get_name() == "Background 2")
            item->init({ 0.0f, 1.5f, -0.3f, 0.0f, 0.0f, 0.0f, 10.0f, 5.0f, 1.0f });
        else if (item->get_name() == "Background 3")
            item->init({ 0.0f, 1.5f, -0.15f, 0.0f, 0.0f, 0.0f, 10.0f, 5.0f, 1.0f });
        else if (item->get_name() == "Shop")
            item->init({ 0.0f, 0.28f, -0.05f, 0.0f, 0.0f, 0.0f, 3.0f, 2.0f, 1.0f });
        else if (item->get_name() == "Floor")
            item->init({ 0.0f, -1.2f, 0.0f, 0.0f, 0.0f, 0.0f, 10.0f, 1.0f, 1.0f });
        else
            item->init({ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f });
    }
}

void Game::object_init()
{
    initialize_camera();
    initialize_players();
    initialize_items();
}
