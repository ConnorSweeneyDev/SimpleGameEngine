#pragma once

#include <string>
#include <fstream>

#include "Render.hpp"

class Shader
{
    public:
        template <typename Type> void setShaderProgram(std::shared_ptr<Type>& object, const std::string vertexShaderPath, const std::string fragmentShaderPath);

        std::string LoadShaderAsString(const std::string& fileName);
        GLuint CompileShader(const GLuint type, const std::string& shaderSource); 
        GLuint CreateShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
        
        void AssignShadersToObjects();
        template <typename Type> void AssignTextureToObject(std::shared_ptr<Type>& object);
};
extern Shader shader;
