#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera
{
    public:
        Camera();

        glm::mat4 getViewMatrix() const;
        
        void moveUp(float speed);
        void moveDown(float speed);
        void moveForward(float speed);
        void moveBackward(float speed);
        void moveLeft(float speed);
        void moveRight(float speed);

    private:
        glm::vec3 cPosition;
        glm::vec3 cDirection;
        glm::vec3 cUp;
};

#endif
