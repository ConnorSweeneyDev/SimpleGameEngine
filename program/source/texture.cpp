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
      {
        player->texture_data.width = redhood_resource_width;
        player->texture_data.height = redhood_resource_height;
        player->texture_data.channels = redhood_resource_channels;
        player->texture_data.data = redhood_resource_data;
      }
      else if (player->name == "Player 2")
      {
        player->texture_data.width = redhood_resource_width;
        player->texture_data.height = redhood_resource_height;
        player->texture_data.channels = redhood_resource_channels;
        player->texture_data.data = redhood_resource_data;
      }
      else
      {
        player->texture_data.width = empty_resource_width;
        player->texture_data.height = empty_resource_height;
        player->texture_data.channels = empty_resource_channels;
        player->texture_data.data = empty_resource_data;
      }

      load(player);
    }

    for (auto &item : items)
    {
      if (item->name == "Background 1")
      {
        item->texture_data.width = background1_resource_width;
        item->texture_data.height = background1_resource_height;
        item->texture_data.channels = background1_resource_channels;
        item->texture_data.data = background1_resource_data;
      }
      else if (item->name == "Background 2")
      {
        item->texture_data.width = background2_resource_width;
        item->texture_data.height = background2_resource_height;
        item->texture_data.channels = background2_resource_channels;
        item->texture_data.data = background2_resource_data;
      }
      else if (item->name == "Background 3")
      {
        item->texture_data.width = background3_resource_width;
        item->texture_data.height = background3_resource_height;
        item->texture_data.channels = background3_resource_channels;
        item->texture_data.data = background3_resource_data;
      }
      else if (item->name == "Shop")
      {
        item->texture_data.width = shop_resource_width;
        item->texture_data.height = shop_resource_height;
        item->texture_data.channels = shop_resource_channels;
        item->texture_data.data = shop_resource_data;
      }
      else if (item->name == "Floor")
      {
        item->texture_data.width = leaffloor_resource_width;
        item->texture_data.height = leaffloor_resource_height;
        item->texture_data.channels = leaffloor_resource_channels;
        item->texture_data.data = leaffloor_resource_data;
      }
      else
      {
        item->texture_data.width = empty_resource_width;
        item->texture_data.height = empty_resource_height;
        item->texture_data.channels = empty_resource_channels;
        item->texture_data.data = empty_resource_data;
      }

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
