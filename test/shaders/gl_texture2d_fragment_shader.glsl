
#version 330 core

layout(location = 0) out vec4 color;

in vec4 v_Color;
in vec2 v_TexCoords;
uniform sampler2D u_Textures[16];
uniform int u_TexIndex;

void main()
{
    color = v_Color;
    color = texture(u_Textures[u_TexIndex], v_TexCoords) * v_Color;
}