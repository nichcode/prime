
#version 330 core

layout(location = 1) in vec4 v_Color;

layout(location = 0) out vec4 color;

void main()
{
    color = v_Color;
}