#pragma once

#include <vector>
#include <memory>

#include <glm/gtc/type_ptr.hpp>

#include "Camera.hpp"

class Player
{
    friend class Render; friend class Shader;

    public:
        Player(std::string name);
        
        const std::string& getName() const;

        void MoveUp();
        void MoveDown();
        void MoveLeft();
        void MoveRight();
        void MoveForward();
        void MoveBackward();

        void RotateXPos(float speed);
        void RotateXNeg(float speed);
        void RotateYPos(float speed);
        void RotateYNeg(float speed);
        void RotateZPos(float speed);
        void RotateZNeg(float speed);

        void ScaleXPos(float speed);
        void ScaleXNeg(float speed);
        void ScaleYPos(float speed);
        void ScaleYNeg(float speed);
        void ScaleZPos(float speed);
        void ScaleZNeg(float speed);

        void ResetStats();
        void ResetPosition();

        void init(
                  float health, float speed,
                  std::vector<float> defaultPosition
                 );

    private:
        std::string name;

        float health;
        float speed;
        std::vector<float> initialStats;

        GLuint vertexArrayObject = 0;
        GLuint vertexBufferObject = 0;
        GLuint indexBufferObject = 0;
        GLuint shaderProgram = 0;
        float translationX;
        float translationY;
        float translationZ;
        float rotationX;
        float rotationY;
        float rotationZ;
        float scaleX;
        float scaleY;
        float scaleZ;
        std::vector<float> initialPosition;
};
using PlayerPtr = std::shared_ptr<Player>;
using PlayerList = std::vector<PlayerPtr>;

PlayerPtr getPlayerByName(const std::string& name);

extern PlayerList players;
