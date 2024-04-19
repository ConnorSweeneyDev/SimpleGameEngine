#include <iostream>
#include <fstream>

#include "shader.hpp"
#include "player.hpp"
#include "item.hpp"

Shader shader;

std::string Shader::load_shader_as_string(const std::string& fileName)
{
    std::string result;

    std::ifstream file(fileName.c_str());
    std::string line;

    if (!file.is_open())
    {
        std::cout << "Unable to open file: " << fileName << "!" << std::endl;
        return result;
    }

    while (std::getline(file, line))
        result += line + "\n";

    file.close();
    return result;
}

GLuint Shader::compile_shader(const GLuint type, const std::string& shaderSource)
{
    GLuint shaderObject;

    if (type == GL_VERTEX_SHADER)
        shaderObject = glCreateShader(GL_VERTEX_SHADER);
    else if (type == GL_FRAGMENT_SHADER)
        shaderObject = glCreateShader(GL_FRAGMENT_SHADER); 
    else
        shaderObject = glCreateShader(GL_NONE);
    
    const char* source = shaderSource.c_str();
    glShaderSource(shaderObject, 1, &source, nullptr);
    glCompileShader(shaderObject);

    int result;
    glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(shaderObject, GL_INFO_LOG_LENGTH, &length);
        char* errorMessages = new char[length];
        glGetShaderInfoLog(shaderObject, length, &length, errorMessages);

        if (type == GL_VERTEX_SHADER)
            std::cout << "GL_VERTEX_SHADER compilation failed!\n" << errorMessages;
        else if (type == GL_FRAGMENT_SHADER)
            std::cout << "GL_FRAGMENT_SHADER compilation failed!\n" << errorMessages;

        delete[] errorMessages;
        glDeleteShader(shaderObject);

        return 0;
    }

    return shaderObject;
}

GLuint Shader::create_shader_program(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
{
    GLuint programObject = glCreateProgram();
    GLuint vertexShader = compile_shader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fragmentShader = compile_shader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    glAttachShader(programObject, vertexShader);
    glAttachShader(programObject, fragmentShader);
    glLinkProgram(programObject);
    glValidateProgram(programObject);

    return programObject;
}

void Shader::assign_shaders_to_objects()
{
    for(auto& player : players)
        shader.set_shader_program(player, "prog/shader/vertex_shader.glsl", "prog/shader/fragment_shader.glsl");

    for(auto& item : items)
        shader.set_shader_program(item, "prog/shader/vertex_shader.glsl", "prog/shader/fragment_shader.glsl");
}
