#include <string>

#include "player.hpp"
#include "rename.hpp"

namespace cse::object
{
  Player_ptr_list players;

  Player::Player(const std::string i_name) : name(i_name) {}

  void Player::move_right() { transform.translation.x += stats.speed; }
  void Player::move_left() { transform.translation.x -= stats.speed; }
  void Player::move_up() { transform.translation.y += stats.speed; }
  void Player::move_down() { transform.translation.y -= stats.speed; }
  void Player::move_forward() { transform.translation.z -= stats.speed; }
  void Player::move_backward() { transform.translation.z += stats.speed; }

  void Player::reset_stats() { stats = initial_stats; }
  void Player::reset_transform() { transform = initial_transform; }

  void Player::init(const float health, const float speed, const glm::Vec3 translation,
                    const glm::Vec3 rotation, const glm::Vec3 scale)
  {
    stats.health = health;
    stats.speed = speed;
    initial_stats = stats;

    transform.translation = translation;
    transform.rotation = rotation;
    transform.scale = scale;
    initial_transform = transform;
  }
}
