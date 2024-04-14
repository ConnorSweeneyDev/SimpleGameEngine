#pragma once

#include <memory>

#include <glad/glad.h>

class Shader
{
    public:
        template <typename Type> void setShaderProgram(std::shared_ptr<Type>& object, const std::string vertexShaderPath, const std::string fragmentShaderPath);

        std::string LoadShaderAsString(const std::string& fileName);
        GLuint CompileShader(const GLuint type, const std::string& shaderSource); 
        GLuint CreateShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
        
        void AssignShadersToObjects();
};
extern Shader shader;
