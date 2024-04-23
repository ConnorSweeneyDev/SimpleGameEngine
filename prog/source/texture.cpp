#define STB_IMAGE_IMPLEMENTATION

#include "texture.hpp"
#include "player.hpp"
#include "item.hpp"

namespace cse
{
    Texture texture;

    void Texture::specify_textures()
    {
        for (auto& player : players)
        {
            if (player->get_name() == "Player 1")
                player->texture_path = "assets/redhood.png";
            else if (player->get_name() == "Player 2")
                player->texture_path = "assets/redhood.png";
            else
                player->texture_path = "assets/empty.png";

            load_texture(player);
        }

        for (auto& item : items)
        {
            if (item->get_name() == "Background 1")
                item->texture_path = "assets/background1.png";
            else if (item->get_name() == "Background 2")
                item->texture_path = "assets/background2.png";
            else if (item->get_name() == "Background 3")
                item->texture_path = "assets/background3.png";
            else if (item->get_name() == "Shop")
                item->texture_path = "assets/shop.png";
            else if (item->get_name() == "Floor")
                item->texture_path = "assets/leaffloor.png";
            else
                item->texture_path = "assets/empty.png";

            load_texture(item);
        }
    }
}
