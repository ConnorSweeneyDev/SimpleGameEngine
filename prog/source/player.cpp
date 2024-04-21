#include "player.hpp"
#include "time.hpp"

namespace cse
{
    Player_ptr_list players;

    Player::Player(std::string name) { this->name = name; }

    const std::string& Player::get_name() const { return name; }

    void Player::move_right() { translation_x += speed * time.get_delta_time(); }
    void Player::move_left() { translation_x -= speed * time.get_delta_time(); }
    void Player::move_up() { translation_y += speed * time.get_delta_time(); }
    void Player::move_down() { translation_y -= speed * time.get_delta_time(); }
    void Player::move_forward() { translation_z -= speed * time.get_delta_time(); }
    void Player::move_backward() { translation_z += speed * time.get_delta_time(); }

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

    void Player::init(float health, float speed,
                      std::vector<float> default_geometry)
    {
        initial_stats.push_back(this->health = health);
        initial_stats.push_back(this->speed = speed);

        initial_geometry.push_back(this->translation_x = default_geometry[0]);
        initial_geometry.push_back(this->translation_y = default_geometry[1]);
        initial_geometry.push_back(this->translation_z = default_geometry[2]);
        initial_geometry.push_back(this->rotation_x = default_geometry[3]);
        initial_geometry.push_back(this->rotation_y = default_geometry[4]);
        initial_geometry.push_back(this->rotation_z = default_geometry[5]);
        initial_geometry.push_back(this->scale_x = default_geometry[6]);
        initial_geometry.push_back(this->scale_y = default_geometry[7]);
        initial_geometry.push_back(this->scale_z = default_geometry[8]);
    }
}
