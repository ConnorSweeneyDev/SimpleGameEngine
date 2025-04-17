#include "texture.hpp"

#include <climits>
#include <utility>

#include "glad.h"
#include "rename.hpp"

#include "item.hpp"
#include "object.hpp"
#include "player.hpp"
#include "render.hpp"
#include "resource.hpp"

namespace cse::object
{
  void Texture::initialize()
  {
    for (auto &player : players)
    {
      if (player->name == "Player 1")
      {
        player->texture_data = resource::redhood_texture_data;
        player->texture_data.total_frames = 2;
      }
      else if (player->name == "Player 2")
      {
        player->texture_data = resource::redhood_texture_data;
        player->texture_data.total_frames = 2;
        player->texture_data.flip_direction = Texture_data::Flip_direction::HORIZONTAL;
      }
      else
        player->texture_data = resource::empty_texture_data;

      update(player);
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

      update(item);
    }
  }

  void Texture::update_all()
  {
    render.call_for_all(
      [](auto object)
      {
        if (object->lifetime_frames % 60 == 0 && object->lifetime_frames != 0)
        {
          object->texture_data.current_frame++;
          if (object->texture_data.current_frame > object->texture_data.total_frames)
            object->texture_data.current_frame = 1;
        }
        object->lifetime_frames++;
        if (object->lifetime_frames == ULLONG_MAX) object->lifetime_frames = 0;
      });
  }

  void Texture::flip_frame(const Texture_data::Flip_direction direction)
  {
    float bottom_left[2];
    float bottom_right[2];
    float top_left[2];
    float top_right[2];
    gl::get_buffer_sub_data(GL_ARRAY_BUFFER, 6 * sizeof(gl::Float), 2 * sizeof(gl::Float), bottom_left);
    gl::get_buffer_sub_data(GL_ARRAY_BUFFER, 14 * sizeof(gl::Float), 2 * sizeof(gl::Float), bottom_right);
    gl::get_buffer_sub_data(GL_ARRAY_BUFFER, 22 * sizeof(gl::Float), 2 * sizeof(gl::Float), top_left);
    gl::get_buffer_sub_data(GL_ARRAY_BUFFER, 30 * sizeof(gl::Float), 2 * sizeof(gl::Float), top_right);

    switch (direction)
    {
      case Texture_data::Flip_direction::NONE: break;
      case Texture_data::Flip_direction::DIAGONAL:
        std::swap(bottom_left, bottom_right);
        std::swap(top_left, top_right);
        std::swap(bottom_left, top_left);
        std::swap(bottom_right, top_right);
        break;
      case Texture_data::Flip_direction::HORIZONTAL:
        std::swap(bottom_left, bottom_right);
        std::swap(top_left, top_right);
        break;
      case Texture_data::Flip_direction::VERTICAL:
        std::swap(bottom_left, top_left);
        std::swap(bottom_right, top_right);
        break;
    }

    gl::buffer_sub_data(GL_ARRAY_BUFFER, 6 * sizeof(gl::Float), 2 * sizeof(gl::Float), &bottom_left);
    gl::buffer_sub_data(GL_ARRAY_BUFFER, 14 * sizeof(gl::Float), 2 * sizeof(gl::Float), &bottom_right);
    gl::buffer_sub_data(GL_ARRAY_BUFFER, 22 * sizeof(gl::Float), 2 * sizeof(gl::Float), &top_left);
    gl::buffer_sub_data(GL_ARRAY_BUFFER, 30 * sizeof(gl::Float), 2 * sizeof(gl::Float), &top_right);
  }

  void Texture::cleanup_buffers()
  {
    gl::bind_vertex_array(0);
    gl::bind_buffer(GL_ARRAY_BUFFER, 0);
    gl::bind_buffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    gl::bind_texture(GL_TEXTURE_2D, 0);
  }
}
