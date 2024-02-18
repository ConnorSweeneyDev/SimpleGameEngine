#pragma once

#include <vector>

#include "glm/gtc/matrix_transform.hpp"

#include "SystemUtil.hpp"
#include "TimeUtil.hpp"

class Camera
{
    public:
        const glm::mat4 getProjectionMatrix() const;
        const glm::mat4 getViewMatrix() const;
        
        void MoveUp(float speed);
        void MoveDown(float speed);
        void MoveLeft(float speed);
        void MoveRight(float speed);
        void MoveForward(float speed);
        void MoveBackward(float speed);
        
        void ResetPosition();

        void init(float fov, float nearClip, float farClip, glm::vec3 position, glm::vec3 direction, glm::vec3 up);

    private:
        float fov;
        float nearClip;
        float farClip;
        glm::vec3 position;
        glm::vec3 direction;
        glm::vec3 up;

        std::vector<glm::vec3> initialPosition;
};
extern Camera camera;
