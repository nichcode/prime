
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoords;

layout(location = 1) out vec2 v_TexCoords;

void main()
{
    gl_Position = vec4(a_Position, 1.0);
    v_TexCoords = a_TexCoords;
}