#pragma once

#include <vector>

#include <glm/glm.hpp>

namespace cse::object
{
    class Camera
    {
        public:
            void update_projection_matrix();
            void update_view_matrix();

            void move_right(float speed);
            void move_left(float speed);
            void move_up(float speed);
            void move_down(float speed);
            void move_forward(float speed);
            void move_backward(float speed);

            void reset_orientation();

            void init(float fov, float near_clip, float far_clip, glm::vec3 position, glm::vec3 direction, glm::vec3 up);

            glm::mat4 projection_matrix = glm::mat4(1.0f);
            glm::mat4 view_matrix = glm::mat4(1.0f);

        private:
            float fov = 0.0f;
            float near_clip = 0.0f;
            float far_clip = 0.0f;
            glm::vec3 position = glm::vec3(0.0f);
            glm::vec3 direction = glm::vec3(0.0f);
            glm::vec3 up = glm::vec3(0.0f);

            std::vector<glm::vec3> initial_orientation = std::vector<glm::vec3>();
    };
    extern Camera camera;
}
