#pragma once

#include <string>
#include <fstream>

#include "Render.hpp"

class Shader
{
    public:
        template <typename Type> void setShaderProgram(std::shared_ptr<Type>& object, std::string vertexShaderPath, std::string fragmentShaderPath);

        std::string LoadShaderAsString(const std::string& fileName);
        GLuint CompileShader(GLuint type, const std::string& shaderSource); 
        GLuint CreateShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
        
        void AssignShadersToObjects();
};
extern Shader shader;
