
#pragma once

static const char* s_VertexSrc = {

	R"(

    #version 330 core

    layout(location = 0) in vec3 a_Position;
    layout(location = 1) in vec4 a_Color;

    layout(location = 1) out vec4 v_Color;

    void main()
    {
        gl_Position = vec4(a_Position, 1.0);
        v_Color = a_Color;
    }

    )"
};

static const char* s_PixelSrc = {

    R"(

    #version 330 core

    layout(location = 0) out vec4 color;

    layout(location = 1) in vec4 v_Color;

    void main()
    {
        color = v_Color;
    }

    )"
};