#pragma once

#include <vector>
#include <memory>

#include <glad/glad.h>

class Item
{
    friend class Render; friend class Shader; friend class Texture;

    public:
        Item(std::string name);
        
        const std::string& getName() const;

        void init(std::vector<float> defaultGeometry);

    private:
        std::string name;

        GLuint vertexArrayObject;
        GLuint vertexBufferObject;
        GLuint indexBufferObject;
        GLuint shaderProgram;
        GLuint textureObject;
        std::string texturePath;
        int textureWidth;
        int textureHeight;
        int textureChannels;

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
using ItemPtrList = std::vector<ItemPtr>;
extern ItemPtrList items;
