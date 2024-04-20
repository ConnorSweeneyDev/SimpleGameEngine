#pragma once

#include <memory>

#include "shader.hpp"

template <typename Type> void Shader::set_shader_program(std::shared_ptr<Type>& object, const std::string vertex_shader_path, const std::string fragment_shader_path)
{
    std::string vertex_shader_source = load_shader_as_string(vertex_shader_path);
    std::string fragment_shader_source = load_shader_as_string(fragment_shader_path);
    object->shader_program = create_shader_program(vertex_shader_source, fragment_shader_source);
}
