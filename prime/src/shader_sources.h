
#pragma once

static const char* s_VertexSource = {

	R"(

    #version 330 core

    layout(location = 0) in vec2 a_Position;
    layout(location = 1) in vec4 a_Color;
    layout(location = 2) in float a_ID;

    layout(location = 1) out vec4 v_Color;
    layout(location = 2) out float v_ID;

    layout(std140) uniform u_ProjectionBlock
    {
	    mat4 u_ViewProjection;
    };

    void main()
    {
        gl_Position = u_ViewProjection * vec4(a_Position, 0.0, 1.0);
        v_Color = a_Color;
        v_ID = a_ID;
    }

    )"
};

static const char* s_PixelSource = {

    R"(

    #version 330 core

    layout (location = 1) in vec4 v_Color;
    layout (location = 2) in float v_ID;

    layout(location = 0) out vec4 color;

    float spriteID = 0.0f;
    float fontID = 1.0f;

    void main()
    {
        if(v_ID == spriteID) {
            color = v_Color;
        }
        else if(v_ID == fontID) {
            color = v_Color;
        }
    }

    )"
};