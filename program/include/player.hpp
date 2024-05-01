#pragma once

#include <vector>
#include <memory>

#include <glad/glad.h>

namespace cse::object
{
    class Player
    {
        friend class Render; friend class Shader; friend class Texture;

        public:
            Player(std::string name);
            
            void move_right();
            void move_left();
            void move_up();
            void move_down();
            void move_forward();
            void move_backward();

            void reset_stats();
            void reset_position();

            void init(float health, float speed,
                      std::vector<float> default_geometry);

            std::string name;

        private:
            float health;
            float speed;
            std::vector<float> initial_stats;

            GLuint vertex_array_object;
            GLuint vertex_buffer_object;
            GLuint index_buffer_object;
            GLuint shader_program;
            GLuint texture_object;
            std::string texture_path;
            int texture_width;
            int texture_height;
            int texture_channels;

            float translation_x;
            float translation_y;
            float translation_z;
            float rotation_x;
            float rotation_y;
            float rotation_z;
            float scale_x;
            float scale_y;
            float scale_z;
            std::vector<float> initial_geometry;
    };
    using Player_ptr = std::shared_ptr<Player>;
    using Player_ptr_list = std::vector<Player_ptr>;
    extern Player_ptr_list players;
}
