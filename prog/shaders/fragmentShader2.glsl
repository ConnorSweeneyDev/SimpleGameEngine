#version 410 core

in vec3 vColor;

out vec4 color;

uniform mat4 uModelMatrix;

void main()
{
    vec4 newColor = vec4(vColor, 1.0f);

    color = newColor;
}
