#pragma once

#include <vector>
#include <memory>

#include <glm/gtc/type_ptr.hpp>

#include "Camera.hpp"

class Item
{
    public:
        Item(std::string name);
        
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

        void init(std::vector<float> defaultPosition);

    private:
        std::string name;

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
};
using ItemPtr = std::shared_ptr<Item>;
using ItemList = std::vector<ItemPtr>;

extern ItemList items;
