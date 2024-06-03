#version 410 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 texture;

out vec3 vertex_color;
out vec2 vertex_texture;

uniform mat4 uniform_projection_matrix;
uniform mat4 uniform_view_matrix;
uniform mat4 uniform_model_matrix;
uniform sampler2D uniform_texture;

void main()
{
  vertex_color = color;
  vertex_texture = texture;

  gl_Position =
    uniform_projection_matrix * uniform_view_matrix * uniform_model_matrix * vec4(position, 1.0f);
}
