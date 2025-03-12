
#pragma once

// ***************************************
//****************sprite******************
// ***************************************

static const char* s_SpriteVertexSrc = {

	R"(

    #version 330 core

    layout(location = 0) in vec2 a_Position;
    layout(location = 1) in vec4 a_Color;
    layout(location = 2) in vec2 a_TextureCoords;
    layout(location = 3) in float a_TextureIndex;

    layout(std140) uniform u_ProjectionBlock
    {
	    mat4 u_ViewProjection;
    };

    out vec4 v_Color;
    out vec2 v_TextureCoords;
    out float v_TextureIndex;

    void main()
    {
        v_Color = a_Color;
        v_TextureCoords = a_TextureCoords;
        v_TextureIndex = a_TextureIndex;
        gl_Position = u_ViewProjection * vec4(a_Position, 0.0, 1.0);
    }

    )"
};

static const char* s_SpritePixelSrc = {

    R"(

    #version 330 core

    layout(location = 0) out vec4 color;

    in vec4 v_Color;
    in vec2 v_TextureCoords;
    in float v_TextureIndex;

    uniform sampler2D u_Textures[16];

    void main()
    {
        int index = int(v_TextureIndex);
        color = texture(u_Textures[index], v_TextureCoords) * v_Color;
    }

    )"
};