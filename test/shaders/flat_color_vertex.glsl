
#version 330 core

layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TextureCoords;

out vec4 v_Color;
out vec2 v_TextureCoords;

void main()
{
    v_Color = a_Color;
    v_TextureCoords = a_TextureCoords;
    gl_Position = vec4(a_Position, 0.0, 1.0);
}