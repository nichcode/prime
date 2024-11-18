#pragma once

#include "prime/defines.h"

namespace prime {

    // sprite
    static str sprite_vertex_shader_source = { 

    R"(
    #version 330 core

    layout(location = 0) in vec2 a_pos;
    layout(location = 1) in vec4 a_color;
    layout(location = 2) in vec2 a_tex_coords;
    layout (location = 3) in float a_tex_index;

    out vec4 v_color;
    out vec2 v_tex_coords;
    out float v_tex_index;

    layout(std140) uniform projection_block
    {
	    mat4 u_view_projection;
    };

    void main()
    {
        v_color = a_color;
        v_tex_coords = a_tex_coords;
        v_tex_index = a_tex_index;
        gl_Position = u_view_projection * vec4(a_pos, 0.0, 1.0);
    }
    )" 
};

    static str sprite_vertex_shader_source_f = {

    R"(
    #version 330 core

    layout(location = 0) in vec2 a_pos;
    layout(location = 1) in vec4 a_color;
    layout(location = 2) in vec2 a_tex_coords;

    out vec4 v_color;
    out vec2 v_tex_coords;

    layout(std140) uniform projection_block
    {
	    mat4 u_view_projection;
    };

    void main()
    {
        v_color = a_color;
        v_tex_coords = a_tex_coords;
        gl_Position = u_view_projection * vec4(a_pos, 0.0, 1.0);
    }
    )"
    };

    static str sprite_pixel_shader_source = {
    
    R"(
    #version 330 core

    layout(location = 0) out vec4 color;

    in vec4 v_color;
    in vec2 v_tex_coords;
    in float v_tex_index;

    uniform sampler2D u_textures[16];

    void main()
    {
        switch(int(v_tex_index))
        {
            case 0: color = texture(u_textures[0], v_tex_coords) * v_color; break;
            case 1: color = texture(u_textures[1], v_tex_coords) * v_color; break;
            case 2: color = texture(u_textures[2], v_tex_coords) * v_color; break;
            case 3: color = texture(u_textures[3], v_tex_coords) * v_color; break;
            case 4: color = texture(u_textures[4], v_tex_coords) * v_color; break;
            case 5: color = texture(u_textures[5], v_tex_coords) * v_color; break;
            case 6: color = texture(u_textures[6], v_tex_coords) * v_color; break;
            case 7: color = texture(u_textures[7], v_tex_coords) * v_color; break;
            case 8: color = texture(u_textures[8], v_tex_coords) * v_color; break;
            case 9: color = texture(u_textures[9], v_tex_coords) * v_color; break;
            case 10: color = texture(u_textures[10], v_tex_coords) * v_color; break;
            case 11: color = texture(u_textures[11], v_tex_coords) * v_color; break;
            case 12: color = texture(u_textures[12], v_tex_coords) * v_color; break;
            case 13: color = texture(u_textures[13], v_tex_coords) * v_color; break;
            case 14: color = texture(u_textures[14], v_tex_coords) * v_color; break;
            case 15: color = texture(u_textures[15], v_tex_coords) * v_color; break;
        }
    }

    )"
};

    static str sprite_pixel_shader_source_f = {

    R"(
    #version 330 core

    layout(location = 0) out vec4 color;

    in vec4 v_color;
    in vec2 v_tex_coords;
    in float v_tex_index;

    uniform sampler2D u_texture;

    void main()
    {
        color = texture(u_texture, v_tex_coords) * v_color;
    }

    )"
    };

}
