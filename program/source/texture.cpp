#define STB_IMAGE_IMPLEMENTATION
#include "rename.hpp"
#include <glad.h>

#include "item.hpp"
#include "player.hpp"
#include "texture.hpp"

namespace cse::object
{
  Texture texture;

  void Texture::specify_all()
  {
    for (auto &player : players)
    {
      if (player->name == "Player 1")
        player->data.texture_path = "assets/redhood.png";
      else if (player->name == "Player 2")
        player->data.texture_path = "assets/redhood.png";
      else
        player->data.texture_path = "assets/empty.png";

      load(player);
    }

    for (auto &item : items)
    {
      if (item->name == "Background 1")
        item->data.texture_path = "assets/background1.png";
      else if (item->name == "Background 2")
        item->data.texture_path = "assets/background2.png";
      else if (item->name == "Background 3")
        item->data.texture_path = "assets/background3.png";
      else if (item->name == "Shop")
        item->data.texture_path = "assets/shop.png";
      else if (item->name == "Floor")
        item->data.texture_path = "assets/leaffloor.png";
      else
        item->data.texture_path = "assets/empty.png";

      load(item);
    }
  }

  void Texture::load_cleanup()
  {
    gl::bind_vertex_array(0);
    gl::bind_buffer(GL_ARRAY_BUFFER, 0);
    gl::bind_buffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    gl::bind_texture(GL_TEXTURE_2D, 0);
  }
}
