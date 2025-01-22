
#include "prime/prime.h"

b8
texture2DTestGL()
{
	prime_LogInfo("");
	prime_LogInfo("Begin Texture2D Test GL");

	prime_Device* device = prime_DeviceCreate(prime_DeviceTypeGL);
	prime_Window* window = prime_WindowCreate("Texture2D Test GL", 640, 480);
	prime_Context* context = prime_ContextCreate(device, window);
	prime_ContextMakeActive(context);
	prime_ContextSetClearColor(context, prime_ColorFromF32(.2f, .2f, .2f, 1.0f));
	prime_ContextSetVsync(context, true);

	f32 vertices[] = {
		// position //  //       color      //  // texture_coords //
		-0.5f, -0.5f,   1.0f, 1.0f, 1.0f, 1.0f,  0.0f, 0.0f, // top right
		 0.5f, -0.5f,   1.0f, 1.0f, 1.0f, 1.0f,  1.0f, 0.0f, // bottom right
		 0.5f,  0.5f,   1.0f, 1.0f, 1.0f, 1.0f,  1.0f, 1.0f, // bottom left
		-0.5f,  0.5f,   1.0f, 1.0f, 1.0f, 1.0f,  0.0f, 1.0f  // top left
	};

	u32 indices[] = { 0, 1, 2, 2, 3, 0 };

	prime_BufferLayout* layout = prime_BufferLayoutCreate();
	prime_BufferElementAdd(layout, prime_BufferElementCreate(prime_DataTypeFloat2));
	prime_BufferElementAdd(layout, prime_BufferElementCreate(prime_DataTypeFloat4));
	prime_BufferElementAdd(layout, prime_BufferElementCreate(prime_DataTypeFloat2));

	prime_Vertexbuffer* vertexbuffer = prime_VertexbufferCreate(
		device,
		nullptr,
		sizeof(vertices),
		prime_VertexbufferTypeDynamic
	);

	prime_BufferLayoutSet(vertexbuffer, layout);

	prime_Indexbuffer* indexbuffer = prime_IndexbufferCreate(
		device, indices, 6);

	prime_VertexbufferSetData(vertexbuffer, vertices, sizeof(vertices));

	prime_Texture2D* texture2d = prime_Texture2DCreate(
		device, 
		1, 
		1, 
		prime_Texture2DFormatRGBA8,
		false);

	prime_Texture2D* texture2d_2 = prime_Texture2DLoad(device, "textures/texture2d.png");

	prime_Texture2DBind(texture2d);
	prime_Texture2DBind(texture2d_2, 1);

	prime_Shader* shader = prime_ShaderCreate(device,
		"shaders/gl_texture2d_vertex_shader.glsl",
		"shaders/gl_texture2d_fragment_shader.glsl");

	prime_ShaderBind(shader);

	i32 samplers[PRIME_MAX_TEXTURE_SLOTS]{};
	for (u32 i = 0; i < PRIME_MAX_TEXTURE_SLOTS; i++) { samplers[i] = i; }

	prime_ShaderSetIntArray(shader, "u_Textures", samplers, PRIME_MAX_TEXTURE_SLOTS);

	while (!prime_WindowShouldClose(window)) {

		prime_WindowPollEvents();

		prime_ContextClear(context);
		prime_ShaderSetInt(shader, "u_TexIndex", 1);
		prime_ContextDrawIndexed(context, prime_DrawModeTriangles, 6);
		prime_ContextSwapbuffers(context);
	}

	prime_BufferLayoutDestroy(layout);
	prime_DeviceDestroy(device);
	prime_WindowDestroy(window);


	prime_LogInfo("End Texture2D Test GL");
	prime_LogInfo("");
	return PRIME_PASSED;
}