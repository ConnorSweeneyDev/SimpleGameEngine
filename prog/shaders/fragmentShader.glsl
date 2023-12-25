#version 410 core

in vec3 vColor;

out vec4 color;

void main()
{
    color = vec4(vColor.r, vColor.g, vColor.b, 1.0f);
}
