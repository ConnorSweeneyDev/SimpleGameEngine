#pragma once

#include <vector>

#include <glm/glm.hpp>
#include "rename.hpp"

namespace cse::object
{
    class Camera
    {
        public:
            void update_projection_matrix();
            void update_view_matrix();

            void move_right(const float speed);
            void move_left(const float speed);
            void move_up(const float speed);
            void move_down(const float speed);
            void move_forward(const float speed);
            void move_backward(const float speed);

            void reset_orientation();

            void init(const float fov, const float near_clip, const float far_clip, const glm::Vec3 position, const glm::Vec3 direction, const glm::Vec3 up);

            glm::Mat4 projection_matrix;
            glm::Mat4 view_matrix;

        private:
            float fov;
            float near_clip;
            float far_clip;
            glm::Vec3 position;
            glm::Vec3 direction;
            glm::Vec3 up;

            std::vector<glm::Vec3> initial_orientation;
    };
    extern Camera camera;
}
