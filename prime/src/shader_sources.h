
#pragma once

static const char* s_SpriteVertexSource = {

	R"(

    #version 330 core

    layout(location = 0) in vec2 a_Position;
    layout(location = 1) in vec4 a_Color;
    layout(location = 2) in vec2 a_Coords;
    layout(location = 3) in vec2 a_Index;

    layout(location = 1) out vec4 v_Color;
    layout(location = 2) out vec2 v_Coords;
    layout(location = 3) out vec2 v_Index;

    layout(std140) uniform u_ProjectionBlock
    {
	    mat4 u_ViewProjection;
    };

    void main()
    {
        gl_Position = u_ViewProjection * vec4(a_Position, 0.0, 1.0);
        v_Color = a_Color;
        v_Index = a_Index;
        v_Coords = a_Coords;
    }

    )"
};

static const char* s_SpritePixelSource = {

    R"(

    #version 330 core

    layout (location = 1) in vec4 v_Color;
    layout (location = 2) in vec2 v_Coords;
    layout (location = 3) in vec2 v_Index;

    layout(location = 0) out vec4 color;

    uniform sampler2D u_Textures[16];

    const float TextureID = 0.0f;
    const float FontID = 1.0f;

    const float width  = 0.5;
    const float edge  = 0.1;

    void main()
    {
        int index = int(v_Index.x);
        if (v_Index.y == TextureID) {
            color = texture(u_Textures[index], v_Coords) * v_Color;
        }
        else if (v_Index.y == FontID) {
            float distance = 1.0 - texture(u_Textures[index], v_Coords).r;
            float alpha = 1.0 - smoothstep(width, width + edge, distance);
            color = vec4(v_Color.x, v_Color.y, v_Color.z, alpha);
        }
    }

    )"
};