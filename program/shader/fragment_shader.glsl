#version 410 core

in vec3 vertex_color;
in vec2 vertex_texture;

out vec4 color;

uniform sampler2D uniform_texture;

void main()
{
  color = texture(uniform_texture, vertex_texture);
  if (color.a == 0.0) discard;
}
