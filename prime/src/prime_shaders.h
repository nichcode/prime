#pragma once


// ***************************************
// sprite
// ***************************************

static const char* s_SpriteVertexSource = {

	R"(

    #version 330 core

    layout(location = 0) in vec2 a_Pos;
    layout(location = 1) in vec2 a_TexCoords;
    layout(location = 2) in float a_TexIndex;

    layout(std140) uniform u_UniformBlock
    {
	    mat4 u_ViewProjection;
        vec4 u_Color;
    };

    out vec4 v_Color;
    out vec2 v_TexCoords;
    out float v_TexIndex;

    void main()
    {
        v_Color = u_Color;
        v_TexCoords = a_TexCoords;
        v_TexIndex = a_TexIndex;
        gl_Position = u_ViewProjection * vec4(a_Pos, 0.0, 1.0);
    }

    )"
};

static const char* s_SpritePixelSource = {

    R"(

    #version 330 core

    layout(location = 0) out vec4 color;

    in vec4 v_Color;
    in vec2 v_TexCoords;
    in float v_TexIndex;
    uniform sampler2D u_Textures[16];

    void main()
    {
        switch(int(v_TexIndex)) {
            case 0: {
                color = texture(u_Textures[0], v_TexCoords) * v_Color;
            }
            break;

        }
    }

    )"
};