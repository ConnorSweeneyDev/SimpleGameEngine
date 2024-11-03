#include "glad.h"
#include "rename.hpp"

#include "item.hpp"
#include "player.hpp"
#include "resource.hpp"
#include "texture.hpp"

namespace cse::object
{
  void Texture::initialize()
  {
    for (auto &player : players)
    {
      if (player->name == "Player 1")
        player->texture_data = resource::redhood_texture_data;
      else if (player->name == "Player 2")
        player->texture_data = resource::redhood_texture_data;
      else
        player->texture_data = resource::empty_texture_data;

      load(player);
    }

    for (auto &item : items)
    {
      if (item->name == "Background 1")
        item->texture_data = resource::background1_texture_data;
      else if (item->name == "Background 2")
        item->texture_data = resource::background2_texture_data;
      else if (item->name == "Background 3")
        item->texture_data = resource::background3_texture_data;
      else if (item->name == "Shop")
        item->texture_data = resource::shop_texture_data;
      else if (item->name == "Floor")
        item->texture_data = resource::leaffloor_texture_data;
      else
        item->texture_data = resource::empty_texture_data;

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
