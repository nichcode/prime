
#pragma once

static const char* s_SpriteVertexSource = {

	R"(

    #version 330 core

    layout(location = 0) in vec4 a_Vertex;
    layout(location = 1) in vec4 a_Color;
    layout(location = 2) in float a_Index;

    layout(location = 0) out vec4 v_Vertex;
    layout(location = 1) out vec4 v_Color;
    layout(location = 2) out float v_Index;

    layout(std140) uniform u_ProjectionBlock
    {
	    mat4 u_ViewProjection;
    };

    void main()
    {
        gl_Position = u_ViewProjection * vec4(a_Vertex.xy, 0.0, 1.0);
        v_Vertex = a_Vertex;
        v_Color = a_Color;
        v_Index = a_Index;
    }

    )"
};

static const char* s_SpritePixelSource = {

    R"(

    #version 330 core

    layout (location = 0) in vec4 v_Vertex;
    layout (location = 1) in vec4 v_Color;
    layout (location = 2) in float v_Index;

    layout(location = 0) out vec4 color;

    uniform sampler2D u_Textures[16];

    void main()
    {
        int index = int(v_Index);
        color = texture(u_Textures[index], v_Vertex.zw) * v_Color;
    }

    )"
};