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
    Player(const std::string i_name);

    void move_right();
    void move_left();
    void move_up();
    void move_down();
    void move_forward();
    void move_backward();

    void reset_stats();
    void reset_position();

    void init(const float i_health, const float i_speed,
              const std::vector<float> i_default_geometry);

    std::string name;

  private:
    struct Player_stats
    {
      float health;
      float speed;
      std::vector<float> initial;
    };
    Player_stats stats;

    Object_transform transform;
    Object_data data;
  };

  using Player_ptr = Object_ptr<Player>;
  using Player_ptr_list = std::vector<Player_ptr>;
  extern Player_ptr_list players;
}
