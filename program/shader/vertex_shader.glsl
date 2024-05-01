#version 410 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texture;

out vec3 v_color;
out vec2 v_texture;

uniform mat4 u_projection_matrix;
uniform mat4 u_view_matrix;
uniform mat4 u_model_matrix;
uniform sampler2D u_texture;

void main()
{
    v_color = color;
    v_texture = texture;

    gl_Position = u_projection_matrix * u_view_matrix * u_model_matrix * vec4(position, 1.0f);
}
