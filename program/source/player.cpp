#include <memory>
#include <string>

#include "rename.hpp"

#include "object.hpp"
#include "player.hpp"

namespace cse::object
{
  Player::Player(const std::string &i_name) : name(i_name) {}

  void Player::move_right() { transform_data.translation.x += stats.speed; }
  void Player::move_left() { transform_data.translation.x -= stats.speed; }
  void Player::move_up() { transform_data.translation.y += stats.speed; }
  void Player::move_down() { transform_data.translation.y -= stats.speed; }
  void Player::move_forward() { transform_data.translation.z -= stats.speed; }
  void Player::move_backward() { transform_data.translation.z += stats.speed; }

  void Player::reset_stats() { stats = *initial_stats; }
  void Player::reset_transform() { transform_data = *initial_transform_data; }

  void Player::initialize(const Stats &i_stats, const Transform_data &i_transform_data)
  {
    stats = i_stats;
    initial_stats = std::make_unique<const Stats>(stats);

    transform_data = i_transform_data;
    initial_transform_data = std::make_unique<const Transform_data>(transform_data);
  }
}
