#pragma once

#include "Player.hpp"
#include "Item.hpp"
#include "Shader.hpp"

class Render
{
    public:
        template <typename Type> void setShaderProgram(std::shared_ptr<Type>& object, std::string vertexShaderPath, std::string fragmentShaderPath);

        void DefineVertices();
        template <typename Type> void SpecifyVertices(std::shared_ptr<Type>& object, std::vector<GLfloat> vertexData, std::vector<GLuint>indexData);
        template <typename Type> void PreDraw(std::shared_ptr<Type>& object); 
        template <typename Type> void Draw(std::shared_ptr<Type>& object);
        
        void predrawinit();

        template <typename Type> void objectcleanup(std::shared_ptr<Type>& player);
        void vertexcleanup();
        void drawcleanup();
};
extern Render render;
