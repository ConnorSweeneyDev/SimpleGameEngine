#pragma once

#include <vector>
#include <memory>

#include <glm/gtc/type_ptr.hpp>

#include "Shader.hpp"
#include "Camera.hpp"

class Player
{
    public:
        Player(std::string name);
        
        const std::string& getName() const;

        void setShaderProgram(std::string vertexShaderPath, std::string fragmentShaderPath);

        void SpecifyVertices(std::vector<GLfloat> vertexData, std::vector<GLuint>indexData);
        void PreDraw();
        void Draw();

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

        void ScaleXUp(float speed);
        void ScaleXDown(float speed);
        void ScaleYUp(float speed);
        void ScaleYDown(float speed);
        void ScaleZUp(float speed);
        void ScaleZDown(float speed);

        void ResetModel();

        void init(float translationX, float translationY, float translationZ, float rotationX, float rotationY, float rotationZ, float scaleX, float scaleY, float scaleZ);
        void cleanup();

    private:
        std::string name;

        GLuint vertexArrayObject = 0;
        GLuint vertexBufferObject = 0;
        GLuint indexBufferObject = 0;
        GLuint shaderProgram = 0;
        
        float translationX = 0.0f;
        float translationY = 0.0f;
        float translationZ = 0.0f;
        float rotationX = 0.0f;
        float rotationY = 0.0f;
        float rotationZ = 0.0f;
        float scaleX = 1.0f;
        float scaleY = 1.0f;
        float scaleZ = 1.0f;

        std::vector<float> initialModel;
};
using PlayerPtr = std::shared_ptr<Player>;
using PlayerList = std::vector<PlayerPtr>;

PlayerPtr getPlayerByName(const std::string& name);

extern PlayerList players;
