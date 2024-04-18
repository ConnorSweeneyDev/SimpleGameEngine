#version 410 core

in vec3 vColor;
in vec2 vTextureCoords;

out vec4 color;

uniform sampler2D uTexture;

void main()
{
    color = texture(uTexture, vTextureCoords);
    if (color.a == 0.0)
        discard;
}
