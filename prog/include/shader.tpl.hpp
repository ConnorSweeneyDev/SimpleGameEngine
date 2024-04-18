#pragma once

#include <memory>

#include "Shader.hpp"

template <typename Type> void Shader::setShaderProgram(std::shared_ptr<Type>& object, const std::string vertexShaderPath, const std::string fragmentShaderPath)
{
    std::string vertexShaderSource = shader.LoadShaderAsString(vertexShaderPath);
    std::string fragmentShaderSource = shader.LoadShaderAsString(fragmentShaderPath);
    object->shaderProgram = shader.CreateShaderProgram(vertexShaderSource, fragmentShaderSource);
}
