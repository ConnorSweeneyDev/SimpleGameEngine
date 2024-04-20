#pragma once

#include <memory>

#include <glad/glad.h>

class Shader
{
    public:
        void specify_shaders();
        template <typename Type> void set_shader_program(std::shared_ptr<Type>& object, const std::string vertex_shader_path, const std::string fragment_shader_path);

        std::string load_shader_as_string(const std::string& file_name);
        GLuint compile_shader(const GLuint type, const std::string& shader_source); 
        GLuint create_shader_program(const std::string& vertex_shader_source, const std::string& fragment_shader_source);
        
};
extern Shader shader;

#include "shader.tpl.hpp"
