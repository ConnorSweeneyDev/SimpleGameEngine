#version 410 core

in vec3 v_color;
in vec2 v_texture;

out vec4 color;

uniform sampler2D u_texture;

void main()
{
    color = texture(u_texture, v_texture);
    if (color.a == 0.0)
        discard;
}
