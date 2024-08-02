#include <string>
#include <vector>

#include "player.hpp"

namespace cse::object
{
  Player_ptr_list players;

  Player::Player(const std::string i_name) : name(i_name) {}

  void Player::move_right() { transform.translation_x += stats.speed; }
  void Player::move_left() { transform.translation_x -= stats.speed; }
  void Player::move_up() { transform.translation_y += stats.speed; }
  void Player::move_down() { transform.translation_y -= stats.speed; }
  void Player::move_forward() { transform.translation_z -= stats.speed; }
  void Player::move_backward() { transform.translation_z += stats.speed; }

  void Player::reset_stats()
  {
    stats.health = stats.initial[0];
    stats.speed = stats.initial[1];
  }

  void Player::reset_position()
  {
    transform.translation_x = transform.initial[0];
    transform.translation_y = transform.initial[1];
    transform.translation_z = transform.initial[2];
    transform.rotation_x = transform.initial[3];
    transform.rotation_y = transform.initial[4];
    transform.rotation_z = transform.initial[5];
    transform.scale_x = transform.initial[6];
    transform.scale_y = transform.initial[7];
    transform.scale_z = transform.initial[8];
  }

  void Player::init(const float health, const float speed,
                    const std::vector<float> default_geometry)
  {
    stats.initial.push_back(stats.health = health);
    stats.initial.push_back(stats.speed = speed);

    transform.initial.push_back(transform.translation_x = default_geometry[0]);
    transform.initial.push_back(transform.translation_y = default_geometry[1]);
    transform.initial.push_back(transform.translation_z = default_geometry[2]);
    transform.initial.push_back(transform.rotation_x = default_geometry[3]);
    transform.initial.push_back(transform.rotation_y = default_geometry[4]);
    transform.initial.push_back(transform.rotation_z = default_geometry[5]);
    transform.initial.push_back(transform.scale_x = default_geometry[6]);
    transform.initial.push_back(transform.scale_y = default_geometry[7]);
    transform.initial.push_back(transform.scale_z = default_geometry[8]);
  }
}
