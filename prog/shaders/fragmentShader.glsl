#version 410 core

in vec3 vColor;

out vec4 color;

uniform mat4 uModelMatrix;

void main()
{
    vec4 newColor = uModelMatrix * vec4(vColor, 1.0f);

    color = vec4(newColor.r, newColor.g, newColor.b + 3.0f, 1.0f);
}
