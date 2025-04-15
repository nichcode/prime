
#include "prime/prime.h"

void onWindowResize(prWindow* window, u32 width, u32 height)
{
    prContext* context = (prContext*)prGetUserData();
    prViewport view;
    view.width = width;
    view.height = height;
    prSetView(view);
}

int main(int argc, char** argv)
{
    prInit();

    u32 flags = prWindowFlags_Center | prWindowFlags_Show;
    prWindow* window = prCreateWindow("window", 640, 480, flags);

    prContextDesc desc;
    desc.type = prContextTypes_OpenGL;
    desc.major = 3;
    desc.minor = 3;
    prContext* context = prCreateContext(window, desc);
    prMakeActive(context);
    prSetVsync(true);

    f32 vertices[] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
		 0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 0.0f
	};

    u32 indices[] = { 0, 1, 2, 2, 3, 0 };

    // layout
    prShaderLayout layout;
    prShaderAttrib position_attrib;
    prShaderAttrib tex_coords_attrib;
    position_attrib.type = prShaderDataTypes_Float3;
    tex_coords_attrib.type = prShaderDataTypes_Float2;
    layout.attribs[0] = position_attrib;
    layout.attribs[1] = tex_coords_attrib;
    layout.count = 2;

    // vertex buffer
    prBufferDesc buffer_desc;
    buffer_desc.type = prBufferTypes_Vertex;
    buffer_desc.data = vertices;
    buffer_desc.size = sizeof(vertices);
    buffer_desc.usage = prBufferUsages_Static;
    prBuffer* vertex_buffer = prCreateBuffer(buffer_desc);

    // index buffer
    buffer_desc.type = prBufferTypes_Index;
    buffer_desc.data = indices;
    buffer_desc.size = sizeof(indices);
    buffer_desc.usage = prBufferUsages_Static;
    prBuffer* index_buffer = prCreateBuffer(buffer_desc);
    
    // shader
    prShaderDesc shader_desc;
    shader_desc.load = true;
    shader_desc.type = prShaderSourceTypes_GLSL;
    shader_desc.vertex_src = "shaders/context_vertex.glsl";
    shader_desc.pixel_src = "shaders/context_pixel.glsl";
    shader_desc.layout = layout;
    prShader* shader = prCreateShader(shader_desc);

    prTexture* texture = prLoadTexture("textures/texture2d.png");

    prBindBuffer(vertex_buffer);
    prBindBuffer(index_buffer);
    prBindShader(shader);
    prBindTexture(texture, 0);
    prSetInt("u_Texture", 0);

    prSetWindowResizedCallback(onWindowResize);
    prSetUserData(context);

    while (!prWindowShouldClose(window)) {
        prPullEvents();

        prClear({ .2f, .2f, .2f, 1.0f });
        prDrawElements(prDrawModes_Triangles, 6);
        prSwapBuffers();
    }

    prSetWindowResizedCallback(nullptr);
    prDestroyContext(context);
    prDestroyWindow(window);
    prShutdown();
    return 0;
}