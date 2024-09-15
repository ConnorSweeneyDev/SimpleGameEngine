#define STB_IMAGE_IMPLEMENTATION
#include "glad.h"
#include "rename.hpp"

#include "item.hpp"
#include "player.hpp"
#include "texture.hpp"

namespace cse::object
{
  void Texture::initialize()
  {
    for (auto &player : players)
    {
      if (player->name == "Player 1")
        player->texture_data.path = "assets/redhood.png";
      else if (player->name == "Player 2")
        player->texture_data.path = "assets/redhood.png";
      else
        player->texture_data.path = "assets/empty.png";

      load(player);
    }

    for (auto &item : items)
    {
      if (item->name == "Background 1")
        item->texture_data.path = "assets/background1.png";
      else if (item->name == "Background 2")
        item->texture_data.path = "assets/background2.png";
      else if (item->name == "Background 3")
        item->texture_data.path = "assets/background3.png";
      else if (item->name == "Shop")
        item->texture_data.path = "assets/shop.png";
      else if (item->name == "Floor")
        item->texture_data.path = "assets/leaffloor.png";
      else
        item->texture_data.path = "assets/empty.png";

      load(item);
    }
  }

  void Texture::cleanup_load()
  {
    gl::bind_vertex_array(0);
    gl::bind_buffer(GL_ARRAY_BUFFER, 0);
    gl::bind_buffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    gl::bind_texture(GL_TEXTURE_2D, 0);
  }
}
