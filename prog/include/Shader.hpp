#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include <glad/glad.h>

class Shader
{
    public:
        std::string LoadShaderAsString(const std::string& fileName);
        
        GLuint CompileShader(GLuint type, const std::string& shaderSource); 
        GLuint CreateShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
};
extern Shader shader;
