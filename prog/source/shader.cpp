#include <iostream>
#include <fstream>

#include "shader.hpp"
#include "player.hpp"
#include "item.hpp"

Shader shader;

void Shader::specify_shaders()
{
    for (auto& player : players)
        set_shader_program(player, "prog/shader/vertex_shader.glsl", "prog/shader/fragment_shader.glsl");

    for (auto& item : items)
        set_shader_program(item, "prog/shader/vertex_shader.glsl", "prog/shader/fragment_shader.glsl");
}

std::string Shader::load_shader_as_string(const std::string& file_name)
{
    std::string result;

    std::ifstream file(file_name.c_str());
    std::string line;

    if (!file.is_open())
    {
        std::cout << "Unable to open file: " << file_name << "!" << std::endl;
        return result;
    }

    while (std::getline(file, line))
        result += line + "\n";

    file.close();
    return result;
}

GLuint Shader::compile_shader(const GLuint type, const std::string& shader_source)
{
    GLuint shader_object;

    if (type == GL_VERTEX_SHADER)
        shader_object = glCreateShader(GL_VERTEX_SHADER);
    else if (type == GL_FRAGMENT_SHADER)
        shader_object = glCreateShader(GL_FRAGMENT_SHADER); 
    else
        shader_object = glCreateShader(GL_NONE);
    
    const char* source = shader_source.c_str();
    glShaderSource(shader_object, 1, &source, nullptr);
    glCompileShader(shader_object);

    int result;
    glGetShaderiv(shader_object, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(shader_object, GL_INFO_LOG_LENGTH, &length);
        char* error_messages = new char[length];
        glGetShaderInfoLog(shader_object, length, &length, error_messages);

        if (type == GL_VERTEX_SHADER)
            std::cout << "GL_VERTEX_SHADER compilation failed!\n" << error_messages;
        else if (type == GL_FRAGMENT_SHADER)
            std::cout << "GL_FRAGMENT_SHADER compilation failed!\n" << error_messages;

        delete[] error_messages;
        glDeleteShader(shader_object);

        return 0;
    }

    return shader_object;
}

GLuint Shader::create_shader_program(const std::string& vertex_shader_source, const std::string& fragment_shader_source)
{
    GLuint program_object = glCreateProgram();
    GLuint vertex_shader = compile_shader(GL_VERTEX_SHADER, vertex_shader_source);
    GLuint fragment_shader = compile_shader(GL_FRAGMENT_SHADER, fragment_shader_source);

    glAttachShader(program_object, vertex_shader);
    glAttachShader(program_object, fragment_shader);
    glLinkProgram(program_object);
    glValidateProgram(program_object);

    return program_object;
}
