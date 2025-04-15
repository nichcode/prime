
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec4 a_Texture;

layout(location = 1) out vec4 v_Color;
layout(location = 2) out vec4 v_Texture;

uniform mat4 u_ViewProjection;

void main()
{
    gl_Position = u_ViewProjection * vec4(a_Position, 1.0); 
    v_Color = a_Color;
    v_Texture = a_Texture;
}