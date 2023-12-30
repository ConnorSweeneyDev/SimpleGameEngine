#version 410 core

layout (location = 0) in vec3 position; // Vertex attribute location 0 is position
layout (location = 1) in vec3 color;    // Vertex attribute location 1 is color

out vec3 vColor; // Output color to the fragment shader

uniform mat4 uProjectionMatrix; // Uniform variables passed from main.cpp to the shader each frame
uniform mat4 uViewMatrix;
uniform mat4 uModelMatrix;

void main()
{
    vColor = color; // Pass the color to the fragment shader

    vec4 newPosition = uProjectionMatrix * uViewMatrix * uModelMatrix * vec4(position, 1.0f); // Order matters

    gl_Position = newPosition;
}
