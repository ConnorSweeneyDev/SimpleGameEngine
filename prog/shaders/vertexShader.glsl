#version 410 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

uniform float uOffsetX;
uniform float uOffsetY;

out vec3 vColor;

void main()
{
    vColor = color;

    gl_Position = vec4(position.x + uOffsetX, position.y + uOffsetY, position.z, 1.0f);
}
