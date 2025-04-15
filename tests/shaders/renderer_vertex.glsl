
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec4 a_Texture;

layout(location = 1) out vec4 v_Color;
layout(location = 2) out vec4 v_Texture;

const float TextureID = 0.0f;
const float FontID = 1.0f;

uniform mat4 u_TextureProjection;
uniform mat4 u_TextProjection;

void main()
{
    if (a_Texture.w == TextureID) {
        gl_Position = u_TextureProjection * vec4(a_Position, 1.0); 
    }

    else if (a_Texture.w == FontID) {
        gl_Position = u_TextProjection * vec4(a_Position, 1.0); 
    }
    
    v_Color = a_Color;
    v_Texture = a_Texture;
}