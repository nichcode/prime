#pragma once


// -------------------------------------
// sprite

static const char* s_SpriteVertexSource = {

	R"(

    #version 330 core

    layout(location = 0) in vec2 a_Position;

    void main()
    {
        gl_Position = vec4(a_Position, 0.0, 1.0);
    }

    )"
};

static const char* s_SpritePixelSource = {

    R"(

    #version 330 core

    layout(location = 0) out vec4 color;

    void main()
    {
        color = vec4(0.0f, 1.0f, 0.0f, 1.0f);
    }

    )"
};

// sprite
// -------------------------------------

