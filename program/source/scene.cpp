#include "rename.hpp"

#include "scene.hpp"
#include "camera.hpp"
#include "player.hpp"
#include "item.hpp"

namespace csg::scene
{
    void specify()
    {
        cse::object::camera.init(45.0f, 0.1f, 10.0f, glm::Vec3(0.0f, 0.0f, 3.0f), glm::Vec3(0.0f, 0.0f, -1.0f), glm::Vec3(0.0f, 1.0f, 0.0f));

        for(auto& player : cse::object::players)
        {
            if (player->name == "Player 1")
                player->init(50, 0.002f,
                             { -1.5f, -0.2f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f });
            else if (player->name == "Player 2")
                player->init(200, 0.0005f,
                             { 1.5f, -0.2f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f }); // Facing the other way, should change to 1.0f and flip the texture instead
            else
                player->init(100, 0.001f,
                             { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f });
        }

        for(auto& item : cse::object::items)
        {
            if (item->name == "Background 1")
                item->init({ 0.0f, 1.5f, -0.45f, 0.0f, 0.0f, 0.0f, 10.0f, 5.0f, 1.0f });
            else if (item->name == "Background 2")
                item->init({ 0.0f, 1.5f, -0.3f, 0.0f, 0.0f, 0.0f, 10.0f, 5.0f, 1.0f });
            else if (item->name == "Background 3")
                item->init({ 0.0f, 1.5f, -0.15f, 0.0f, 0.0f, 0.0f, 10.0f, 5.0f, 1.0f });
            else if (item->name == "Shop")
                item->init({ 0.0f, 0.28f, -0.05f, 0.0f, 0.0f, 0.0f, 3.0f, 2.0f, 1.0f });
            else if (item->name == "Floor")
                item->init({ 0.0f, -1.2f, 0.0f, 0.0f, 0.0f, 0.0f, 10.0f, 1.0f, 1.0f });
            else
                item->init({ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f });
        }
    }
}
