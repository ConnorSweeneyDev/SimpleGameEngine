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

void Item::init(std::vector<float> defaultPosition)
{
    this->translationX = defaultPosition[0];
    this->translationY = defaultPosition[1];
    this->translationZ = defaultPosition[2];
    this->rotationX = defaultPosition[3];
    this->rotationY = defaultPosition[4];
    this->rotationZ = defaultPosition[5];
    this->scaleX = defaultPosition[6];
    this->scaleY = defaultPosition[7];
    this->scaleZ = defaultPosition[8];
}
