#version 410 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec3 vColor;

uniform mat4 uModelMatrix;

void main()
{
    vColor = color;

    vec4 newPosition = uModelMatrix * vec4(position, 1.0f);

    gl_Position = vec4(newPosition.x, newPosition.y, newPosition.z, 1.0f);
}
