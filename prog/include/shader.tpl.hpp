#pragma once

#include <memory>

#include "shader.hpp"

template <typename Type> void Shader::set_shader_program(std::shared_ptr<Type>& object, const std::string vertexShaderPath, const std::string fragmentShaderPath)
{
    std::string vertexShaderSource = shader.load_shader_as_string(vertexShaderPath);
    std::string fragmentShaderSource = shader.load_shader_as_string(fragmentShaderPath);
    object->shaderProgram = shader.create_shader_program(vertexShaderSource, fragmentShaderSource);
}
