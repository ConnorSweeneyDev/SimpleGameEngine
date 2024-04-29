#pragma once

#include <memory>

#include <glad/glad.h>

namespace cse::object
{
    class Shader
    {
        public:
            void specify();
            template <typename Type> void set_program(std::shared_ptr<Type>& object, const std::string vertex_shader_path, const std::string fragment_shader_path);

        private:
            std::string load_as_string(const std::string& file_name);
            GLuint compile(const GLuint type, const std::string& shader_source); 
            GLuint create_program(const std::string& vertex_shader_source, const std::string& fragment_shader_source);
            
    };
    extern Shader shader;
}

#include "shader.tpl.hpp"
