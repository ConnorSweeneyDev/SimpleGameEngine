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
        void moveLeft(float speed);
        void moveRight(float speed);
        void moveForward(float speed);
        void moveBackward(float speed);

    private:
        glm::vec3 cPosition;  // Camera position
        glm::vec3 cDirection; // Camera look direction
        glm::vec3 cUp;        // Camera up direction
};

#endif
