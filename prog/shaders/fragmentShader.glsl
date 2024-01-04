#version 410 core

in vec3 vColor;

out vec4 color;

uniform mat4 uModelMatrix;

void main()
{
    vec4 newColor = uModelMatrix * vec4(vColor.r + 1.5, vColor.g + 0.2, vColor.b, 1.0f); // Order of multiplication matters

    color = newColor;
}
