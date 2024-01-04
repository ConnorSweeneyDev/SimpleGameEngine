#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

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

        void init();

    private:
        glm::vec3 position;
        glm::vec3 direction;
        glm::vec3 up;
};
extern Camera camera;
