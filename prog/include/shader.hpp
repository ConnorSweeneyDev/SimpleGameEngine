#pragma once

#include <memory>

#include <glad/glad.h>

class Shader
{
    public:
        template <typename Type> void set_shader_program(std::shared_ptr<Type>& object, const std::string vertexShaderPath, const std::string fragmentShaderPath);

        std::string load_shader_as_string(const std::string& fileName);
        GLuint compile_shader(const GLuint type, const std::string& shaderSource); 
        GLuint create_shader_program(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
        
        void assign_shaders_to_objects();
};
extern Shader shader;

#include "shader.tpl.hpp"
