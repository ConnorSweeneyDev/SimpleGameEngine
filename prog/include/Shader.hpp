#pragma once

#include <iostream> // Console output
#include <fstream> // File input and output
#include <string> // std::string, std::getline

#include <glad/glad.h> // Load OpenGL functions

class Shader // Stores utility functions for shaders
{
    public:
        std::string LoadShaderAsString(const std::string& fileName);
        
        GLuint CompileShader(GLuint type, const std::string& shaderSource); 
        GLuint CreateShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
};
extern Shader shader;
