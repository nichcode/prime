
#version 330 core

layout(location = 0) out vec4 color;

in vec4 v_Color;
in vec2 v_TexCoords;

uniform sampler2D u_Texture;

void main()
{
    color = texture(u_Texture, v_TexCoords) * v_Color;
}