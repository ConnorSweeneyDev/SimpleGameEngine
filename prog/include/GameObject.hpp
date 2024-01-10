#pragma once

#include <vector>
#include <memory>

#include <glm/gtc/type_ptr.hpp>

#include "Shader.hpp"
#include "Camera.hpp"

class GameObject
{
    public:
        GameObject(std::string name);
        
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

        void ScaleUp(float speed);
        void ScaleDown(float speed);

        void Reset();

        void init(float translationX, float translationY, float translationZ, float rotationX, float rotationY, float rotationZ, float scale);
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
        float scale = 1.0f;

        std::vector<float> initial;
};
using GameObjectPtr = std::shared_ptr<GameObject>;
using GameObjectList = std::vector<GameObjectPtr>;

GameObjectPtr getGameObjectByName(const std::string& name);

extern GameObjectList game_objects;
