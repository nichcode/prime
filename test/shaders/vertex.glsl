
#version 330 core

layout(location = 0) in vec3 a_Pos;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoords;
layout(location = 3) in vec2 a_TexCoords2;

out vec4 v_Color;
out vec2 v_TexCoords;
out vec2 v_TexCoords2;

void main()
{
    v_Color = a_Color;
    v_TexCoords = a_TexCoords;
    v_TexCoords2 = a_TexCoords2;
    gl_Position = vec4(a_Pos, 1.0);
}