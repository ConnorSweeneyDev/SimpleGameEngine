#pragma once

#include <vector>

#include "glm/gtc/matrix_transform.hpp"

#include "Util.hpp"

class Camera
{
    public:
        glm::mat4 getViewMatrix() const;
        
        void MoveUp(float speed);
        void MoveDown(float speed);
        void MoveLeft(float speed);
        void MoveRight(float speed);
        void MoveForward(float speed);
        void MoveBackward(float speed);
        
        void ResetPosition();

        void init(glm::vec3 position, glm::vec3 direction, glm::vec3 up);

    private:
        glm::vec3 position;
        glm::vec3 direction;
        glm::vec3 up;

        std::vector<glm::vec3> initial;
};
extern Camera camera;
