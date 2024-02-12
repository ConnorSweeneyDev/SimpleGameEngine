#pragma once

#include <vector>
#include <memory>

#include <glm/gtc/type_ptr.hpp>

#include "Camera.hpp"

class Item
{
    friend class Render; friend class Shader;

    public:
        Item(std::string name);
        
        const std::string& getName() const;

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
using ItemPtrList = std::vector<ItemPtr>;

ItemPtr getItemByName(const std::string& name);

extern ItemPtrList items;
