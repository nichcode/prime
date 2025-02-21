#pragma once


// ***************************************
// sprite
// ***************************************

static const char* s_SpriteVertexSource = {

	R"(

    #version 330 core

    layout(location = 0) in vec2 a_Pos;
    layout(location = 1) in vec4 a_Color;
    layout(location = 2) in vec2 a_TexCoords;
    layout(location = 3) in float a_TexIndex;

    layout(std140) uniform u_UniformBlock
    {
	    mat4 u_ViewProjection;
    };

    out vec4 v_Color;
    out vec2 v_TexCoords;
    out float v_TexIndex;

    void main()
    {
        v_Color = a_Color;
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
            case 0: color = texture(u_Textures[0], v_TexCoords) * v_Color; break;
            case 1: color = texture(u_Textures[1], v_TexCoords) * v_Color; break;
            case 2: color = texture(u_Textures[2], v_TexCoords) * v_Color; break;
            case 3: color = texture(u_Textures[3], v_TexCoords) * v_Color; break;
            case 4: color = texture(u_Textures[4], v_TexCoords) * v_Color; break;
            case 5: color = texture(u_Textures[5], v_TexCoords) * v_Color; break;
            case 6: color = texture(u_Textures[6], v_TexCoords) * v_Color; break;
            case 7: color = texture(u_Textures[7], v_TexCoords) * v_Color; break;
            case 8: color = texture(u_Textures[8], v_TexCoords) * v_Color; break;
            case 9: color = texture(u_Textures[9], v_TexCoords) * v_Color; break;
            case 10: color = texture(u_Textures[10], v_TexCoords) * v_Color; break;
            case 11: color = texture(u_Textures[11], v_TexCoords) * v_Color; break;
            case 12: color = texture(u_Textures[12], v_TexCoords) * v_Color; break;
            case 13: color = texture(u_Textures[13], v_TexCoords) * v_Color; break;
            case 14: color = texture(u_Textures[14], v_TexCoords) * v_Color; break;
            case 15: color = texture(u_Textures[15], v_TexCoords) * v_Color; break;
        }
    }

    )"
};