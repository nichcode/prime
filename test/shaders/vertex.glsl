
#version 330 core

layout(location = 0) in vec3 a_position;

layout(std140) uniform u_ProjectionBlock
{
    mat4 u_ViewProjection;
};

void main()
{
    gl_Position = u_ViewProjection * vec4(a_position, 1.0);
}