#pragma once

#include <fstream>

#include "Render.hpp"

class Shader
{
    public:
        std::string LoadShaderAsString(const std::string& fileName);
        
        template <typename Type> void setShaderProgram(std::shared_ptr<Type>& object, std::string vertexShaderPath, std::string fragmentShaderPath);

        GLuint CompileShader(GLuint type, const std::string& shaderSource); 
        GLuint CreateShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
};
extern Shader shader;
