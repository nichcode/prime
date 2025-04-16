
#pragma once

static const char* s_VertexSource = {

	R"(

    #version 330 core

    layout(location = 0) in vec3 a_Position;
    layout(location = 1) in vec4 a_Color;
    layout(location = 2) in vec4 a_Texture;

    layout(location = 1) out vec4 v_Color;
    layout(location = 2) out vec4 v_Texture;

    uniform mat4 u_ViewProjection;

    void main()
    {
        gl_Position = u_ViewProjection * vec4(a_Position, 1.0); 
        v_Color = a_Color;
        v_Texture = a_Texture;
    }

    )"
};

static const char* s_PixelSource = {

    R"(

    #version 330 core

    layout(location = 1) in vec4 v_Color;
    layout(location = 2) in vec4 v_Texture;

    layout(location = 0) out vec4 color;

    uniform sampler2D u_Textures[16];

    const float TextureID = 0.0f;
    const float FontID = 1.0f;
    const float width  = 0.5;
    const float edge  = 0.1;

    void main()
    {
        int index = int(v_Texture.z);
        if (v_Texture.w == TextureID) {
            color = texture(u_Textures[index], v_Texture.xy) * v_Color;
        }

        else if (v_Texture.w == FontID) {
            float distance = 1.0 - texture(u_Textures[index], v_Texture.xy).r;
            float alpha = 1.0 - smoothstep(width, width + edge, distance);
            color = vec4(v_Color.xyz, alpha);
        }
    }

    )"
};