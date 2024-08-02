#pragma once

#include <string>
#include <vector>

#include "rename.hpp"

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
    void reset_transform();

    void init(const float health, const float speed, const glm::Vec3 translation,
              const glm::Vec3 rotation, const glm::Vec3 scale);

    std::string name;

  private:
    struct Player_stats
    {
      float health;
      float speed;
    };
    Player_stats stats;
    Player_stats initial_stats;

    Object_transform transform;
    Object_transform initial_transform;
    Object_data data;
  };

  using Player_ptr = Object_ptr<Player>;
  using Player_ptr_list = std::vector<Player_ptr>;
  extern Player_ptr_list players;
}
