#pragma once

#include <vector>
#include <memory>

#include <glm/gtc/type_ptr.hpp>

#include "Camera.hpp"

class Player
{
    public:
        Player(std::string name);
        
        const std::string& getName() const;
        GLuint& getVertexArrayObject();
        GLuint& getVertexBufferObject();
        GLuint& getIndexBufferObject();
        GLuint& getShaderProgram();
        float& getTranslationX();
        float& getTranslationY();
        float& getTranslationZ();
        float& getRotationX();
        float& getRotationY();
        float& getRotationZ();
        float& getScaleX();
        float& getScaleY();
        float& getScaleZ();

        void MoveUp();
        void MoveDown();
        void MoveLeft();
        void MoveRight();
        void MoveForward();
        void MoveBackward();

        void ResetPosition();
        void ResetStats();

        void init(float translationX, float translationY, float translationZ, float rotationX, float rotationY, float rotationZ, float scaleX, float scaleY, float scaleZ,
                  float health, float speed);

    private:
        std::string name;

        float health;
        float speed;

        float translationX;
        float translationY;
        float translationZ;
        float rotationX;
        float rotationY;
        float rotationZ;
        float scaleX;
        float scaleY;
        float scaleZ;

        GLuint vertexArrayObject = 0;
        GLuint vertexBufferObject = 0;
        GLuint indexBufferObject = 0;
        GLuint shaderProgram = 0;        

        std::vector<float> initialPosition;
        std::vector<float> initialStats;
};
using PlayerPtr = std::shared_ptr<Player>;
using PlayerList = std::vector<PlayerPtr>;

PlayerPtr getPlayerByName(const std::string& name);

extern PlayerList players;