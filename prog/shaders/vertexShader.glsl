#version 410 core

layout (location = 0) in vec3 positions;
layout (location = 1) in vec3 color;

out vec3 vVertexColor;

void main()
{
    vVertexColor = color;

    gl_Position = vec4(positions.x, positions.y, positions.z, 1.0f);
}
