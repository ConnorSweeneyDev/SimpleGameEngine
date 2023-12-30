#version 410 core

in vec3 vColor; // Interpolated values from the vertex shaders

out vec4 color; // Output data to main.cpp

uniform mat4 uModelMatrix; // Uniform passed from main.cpp to the shader each time

void main()
{
    vec4 newColor = uModelMatrix * vec4(vColor, 1.0f); // Order matters

    color = newColor;
}
