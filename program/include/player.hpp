#pragma once

#include <memory>
#include <string>
#include <vector>

#include "data.hpp"
#include "item.hpp"

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

  public:
    Player(const std::string &i_name);

    void initialize(const Stats &i_stats, const Transform_data &i_transform_data);

    void move_right();
    void move_left();
    void move_up();
    void move_down();
    void move_forward();
    void move_backward();
    void reset_transform();

    void reset_stats();

  public:
    std::string name = "";

  private:
    Stats stats = {};
    std::unique_ptr<const Stats> initial_stats = {};

    Transform_data transform_data = {};
    std::unique_ptr<const Transform_data> initial_transform_data = {};
    Render_data render_data = {};
    Texture_data texture_data = {};
    Shader_data shader_data = {};
    unsigned long long lifetime_frames = 0;
  };

  using Player_pointer = Object_pointer<Player>;
  using Player_pointer_list = std::vector<Player_pointer>;
  inline Player_pointer_list players = {};
}
