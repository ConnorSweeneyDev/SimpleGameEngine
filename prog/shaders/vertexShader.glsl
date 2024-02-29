#version 410 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 textureCoords;

out vec3 vColor;
out vec2 vTextureCoords;

uniform mat4 uProjectionMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uModelMatrix;
uniform sampler2D uTexture;

void main()
{
    vColor = color;
    vTextureCoords = textureCoords;

    gl_Position = uProjectionMatrix * uViewMatrix * uModelMatrix * vec4(position, 1.0f); // Order of multiplication matters
}
