#version 410 core

uniform float uOffsetX;
uniform float uOffsetY;

in vec3 vColor;

out vec4 color;

void main()
{
    color = vec4(vColor.r + uOffsetX + uOffsetY, vColor.g + uOffsetX + uOffsetY, vColor.b + uOffsetX + uOffsetY, 1.0f);
}
