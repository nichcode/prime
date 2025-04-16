
#include "PAL/PAL.h"

void onWindowResize(PAL_Window* window, u32 width, u32 height)
{
    PAL_Viewport view;
    view.width = width;
    view.height = height;
    PAL_SetViewport(view);
}

int main(int argc, char** argv)
{
    PAL_Init();

    u32 flags = PAL_WindowFlags_Center | PAL_WindowFlags_Show;
    PAL_Window* window = PAL_CreateWindow("window", 640, 480, flags);

    PAL_ContextDesc desc;
    desc.type = PAL_ContextTypes_OpenGL;
    desc.major = 3;
    desc.minor = 3;
    PAL_Context* context = PAL_CreateContext(window, desc);
    PAL_MakeActive(context);
    PAL_SetVsync(true);

    f32 vertices[] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
		 0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 0.0f
	};

    u32 indices[] = { 0, 1, 2, 2, 3, 0 };

    // layout
    PAL_ShaderLayout layout;
    PAL_ShaderAttrib position_attrib;
    PAL_ShaderAttrib tex_coords_attrib;
    position_attrib.type = PAL_ShaderDataTypes_Float3;
    tex_coords_attrib.type = PAL_ShaderDataTypes_Float2;
    layout.attribs[0] = position_attrib;
    layout.attribs[1] = tex_coords_attrib;
    layout.count = 2;

    // vertex buffer
    PAL_BufferDesc buffer_desc;
    buffer_desc.type = PAL_BufferTypes_Vertex;
    buffer_desc.data = vertices;
    buffer_desc.size = sizeof(vertices);
    buffer_desc.usage = PAL_BufferUsages_Static;
    PAL_Buffer* vertex_buffer = PAL_CreateBuffer(buffer_desc);

    // index buffer
    buffer_desc.type = PAL_BufferTypes_Index;
    buffer_desc.data = indices;
    buffer_desc.size = sizeof(indices);
    buffer_desc.usage = PAL_BufferUsages_Static;
    PAL_Buffer* index_buffer = PAL_CreateBuffer(buffer_desc);
    
    // shader
    PAL_ShaderDesc shader_desc;
    shader_desc.load = true;
    shader_desc.type = PAL_ShaderSourceTypes_GLSL;
    shader_desc.vertex_src = "shaders/vertex.glsl";
    shader_desc.pixel_src = "shaders/pixel.glsl";
    shader_desc.layout = layout;
    PAL_Shader* shader = PAL_CreateShader(shader_desc);

    PAL_Texture* texture = PAL_LoadTexture("textures/texture2d.png");

    PAL_BindBuffer(vertex_buffer);
    PAL_BindBuffer(index_buffer);
    PAL_BindShader(shader);
    PAL_BindTexture(texture, 0);
    PAL_SetInt("u_Texture", 0);

    PAL_SetWindowResizedCallback(onWindowResize);

    while (!PAL_WindowShouldClose(window)) {
        PAL_PullEvents();

        PAL_Clear({ .2f, .2f, .2f, 1.0f });
        PAL_DrawElements(PAL_DrawModes_Triangles, 6);
        PAL_SwapBuffers();
    }

    PAL_SetWindowResizedCallback(nullptr);
    PAL_DestroyContext(context);
    PAL_DestroyWindow(window);
    PAL_Shutdown();
    return 0;
}