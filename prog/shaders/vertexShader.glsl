#version 410 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec3 vColor;

uniform mat4 uModelMatrix;
uniform mat4 uProjectionMatrix;

void main()
{
    vColor = color;

    vec4 newPosition = uProjectionMatrix * uModelMatrix * vec4(position, 1.0f);

    gl_Position = newPosition;
}
