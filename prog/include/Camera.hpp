#pragma once

#include <vector>

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/rotate_vector.hpp"

#include "SystemUtil.hpp"
#include "TimeUtil.hpp"

class Camera
{
    public:
        const glm::mat4& getProjectionMatrix() const;
        const glm::mat4& getViewMatrix() const;
        
        void UpdateProjectionMatrix();
        void UpdateViewMatrix();

        void MoveUp(float speed);
        void MoveDown(float speed);
        void MoveLeft(float speed);
        void MoveRight(float speed);
        void MoveForward(float speed);
        void MoveBackward(float speed);

        void RotateXPos(float speed);
        void RotateXNeg(float speed);
        void RotateYPos(float speed);
        void RotateYNeg(float speed);
        void RotateZPos(float speed);
        void RotateZNeg(float speed);
        
        void ResetPosition();

        void init(float fov, float nearClip, float farClip, glm::vec3 position, glm::vec3 direction, glm::vec3 up);

    private:
        float fov;
        float nearClip;
        float farClip;
        glm::vec3 position;
        glm::vec3 direction;
        glm::vec3 up;

        glm::mat4 projectionMatrix;
        glm::mat4 viewMatrix;

        std::vector<glm::vec3> initialPosition;
};
extern Camera camera;
