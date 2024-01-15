#version 410 core

out vec4 color;

void main()
{
    vec4 newColor = vec4(0.1f, 0.1f, 0.1f, 1.0f); // Order of multiplication matters

    color = newColor;
}
