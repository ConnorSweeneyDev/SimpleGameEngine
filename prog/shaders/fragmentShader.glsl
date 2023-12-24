#version 410 core

in vec3 vVertexColor;

out vec4 color;

void main()
{
    color = vec4(vVertexColor.r, vVertexColor.g, vVertexColor.b, 1.0f);
}
