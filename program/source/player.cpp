#include "player.hpp"
#include "time.hpp"

namespace cse::object
{
    Player_ptr_list players;

    Player::Player(const std::string i_name) : name(i_name) {}

    void Player::move_right() { translation_x += speed * time::delta_time; }
    void Player::move_left() { translation_x -= speed * time::delta_time; }
    void Player::move_up() { translation_y += speed * time::delta_time; }
    void Player::move_down() { translation_y -= speed * time::delta_time; }
    void Player::move_forward() { translation_z -= speed * time::delta_time; }
    void Player::move_backward() { translation_z += speed * time::delta_time; }

    void Player::reset_stats()
    {
        health = initial_stats[0];
        speed = initial_stats[1];
    }

    void Player::reset_position()
    {
        translation_x = initial_geometry[0];
        translation_y = initial_geometry[1];
        translation_z = initial_geometry[2];
        rotation_x = initial_geometry[3];
        rotation_y = initial_geometry[4];
        rotation_z = initial_geometry[5];
        scale_x = initial_geometry[6];
        scale_y = initial_geometry[7];
        scale_z = initial_geometry[8];
    }

    void Player::init(const float i_health, const float i_speed,
                      const std::vector<float> i_default_geometry)
    {
        initial_stats.push_back(health = i_health);
        initial_stats.push_back(speed = i_speed);

        initial_geometry.push_back(translation_x = i_default_geometry[0]);
        initial_geometry.push_back(translation_y = i_default_geometry[1]);
        initial_geometry.push_back(translation_z = i_default_geometry[2]);
        initial_geometry.push_back(rotation_x = i_default_geometry[3]);
        initial_geometry.push_back(rotation_y = i_default_geometry[4]);
        initial_geometry.push_back(rotation_z = i_default_geometry[5]);
        initial_geometry.push_back(scale_x = i_default_geometry[6]);
        initial_geometry.push_back(scale_y = i_default_geometry[7]);
        initial_geometry.push_back(scale_z = i_default_geometry[8]);
    }
}
