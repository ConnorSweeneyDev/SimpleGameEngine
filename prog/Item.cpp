#include "Item.hpp"

ItemList items;

Item::Item(std::string name) { this->name = name; }

const std::string& Item::getName() const { return name; }
GLuint& Item::getVertexArrayObject() { return vertexArrayObject; }
GLuint& Item::getVertexBufferObject() { return vertexBufferObject; }
GLuint& Item::getIndexBufferObject() { return indexBufferObject; }
GLuint& Item::getShaderProgram() { return shaderProgram; }
float& Item::getTranslationX() { return translationX; }
float& Item::getTranslationY() { return translationY; }
float& Item::getTranslationZ() { return translationZ; }
float& Item::getRotationX() { return rotationX; }
float& Item::getRotationY() { return rotationY; }
float& Item::getRotationZ() { return rotationZ; }
float& Item::getScaleX() { return scaleX; }
float& Item::getScaleY() { return scaleY; }
float& Item::getScaleZ() { return scaleZ; }

void Item::init(float translationX, float translationY, float translationZ, float rotationX, float rotationY, float rotationZ, float scaleX, float scaleY, float scaleZ)
{
    this->translationX = translationX;
    this->translationY = translationY;
    this->translationZ = translationZ;
    this->rotationX = rotationX;
    this->rotationY = rotationY;
    this->rotationZ = rotationZ;
    this->scaleX = scaleX;
    this->scaleY = scaleY;
    this->scaleZ = scaleZ;
}

ItemPtr getItemByName(const std::string &name)
{
    for (auto &item : items)
    {
        if (item->getName() == name)
        {
            return item;
        }
    }
    return nullptr;
}
