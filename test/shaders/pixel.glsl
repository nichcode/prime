
#version 330 core

layout(location = 0) out vec4 color;

in vec4 v_Color;
in vec2 v_TexCoords;
in vec2 v_TexCoords2;

uniform int u_TexCoordsIndex;

uniform sampler2D u_Texture;

void main()
{
    if (u_TexCoordsIndex == 0) {
        color = texture(u_Texture, v_TexCoords) * v_Color;
    }
    else {
        color = texture(u_Texture, v_TexCoords2) * v_Color;
    }
}