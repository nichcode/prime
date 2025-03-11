
#pragma once

// ***************************************
//****************sprite******************
// ***************************************

static const char* s_SpriteVertexSrc = {

	R"(

    #version 330 core

    layout(location = 0) in vec2 a_Position;

    layout(std140) uniform u_ProjectionBlock
    {
	    mat4 u_ViewProjection;
    };

    void main()
    {
        gl_Position = u_ViewProjection * vec4(a_Position, 0.0, 1.0);
    }

    )"
};

static const char* s_SpritePixelSrc = {

    R"(

    #version 330 core

    layout(location = 0) out vec4 color;

    void main()
    {
        color = vec4(1.0, 0.0, 0.0, 1.0);
    }

    )"
};