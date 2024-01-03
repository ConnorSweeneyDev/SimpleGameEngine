#version 410 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec3 vColor;

uniform mat4 uProjectionMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uModelMatrix;

void main()
{
    vColor = color;

    vec4 newPosition = uProjectionMatrix * uViewMatrix * uModelMatrix * vec4(position, 1.0f); // Order of multiplication matters

    gl_Position = newPosition;
}
