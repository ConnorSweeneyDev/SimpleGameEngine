#pragma once

#include <string>
#include <vector>

#include "object.hpp"

namespace cse::object
{
  class Player
  {
    friend class Render;
    friend class Shader;
    friend class Texture;

  public:
    struct Stats
    {
      float health = 0.0f;
      float speed = 0.0f;
    };

    Player(const std::string i_name);

    void move_right();
    void move_left();
    void move_up();
    void move_down();
    void move_forward();
    void move_backward();

    void reset_stats();
    void reset_transform();

    void initialize(const Stats &i_stats, const Transform_data &i_transform_data);

    std::string name = "";

  private:
    Stats stats = {};
    Stats initial_stats = {};
    Transform_data transform_data = {};
    Transform_data initial_transform_data = {};

    Texture_data texture_data = {};
    Shader_data shader_data = {};
    Render_data render_data = {};
  };

  using Player_ptr = Object_ptr<Player>;
  using Player_ptr_list = std::vector<Player_ptr>;
  inline Player_ptr_list players = {};
}
