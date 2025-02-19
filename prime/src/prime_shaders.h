#pragma once


// ***************************************
// sprite
// ***************************************

static const char* s_SpriteVertexSource = {

	R"(

    #version 330 core

    layout(location = 0) in vec2 a_Pos;

    layout(std140) uniform u_UniformBlock
    {
	    mat4 u_ViewProjection;
        vec4 u_Color;
    };

    out vec4 v_Color;

    void main()
    {
        v_Color = u_Color;
        gl_Position = u_ViewProjection * vec4(a_Pos, 0.0, 1.0);
    }

    )"
};

static const char* s_SpritePixelSource = {

    R"(

    #version 330 core

    layout(location = 0) out vec4 color;

    in vec4 v_Color;

    void main()
    {
        color = v_Color;
    }

    )"
};