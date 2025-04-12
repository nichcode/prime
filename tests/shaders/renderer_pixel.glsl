
#version 330 core

layout(location = 1) in vec4 v_Color;
layout(location = 2) in vec4 v_Texture;

layout(location = 0) out vec4 color;

uniform sampler2D u_Textures[16];

void main()
{
    int index = int(v_Texture.z);
    color = texture(u_Textures[index], v_Texture.xy) * v_Color;
}