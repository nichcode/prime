
#include "prime/prime.h"

b8
shaderTestGL()
{
	prime_LogInfo("");
	prime_LogInfo("Begin Shader Test GL");

	prime_Device* device = prime_DeviceCreate(prime_DeviceTypeGL);
	prime_Window* window = prime_WindowCreate("Shader Test GL", 640, 480);
	prime_Context* context = prime_ContextCreate(device, window);
	prime_ContextMakeActive(context);
	prime_ContextSetClearColor(context, prime_ColorFromF32(.2f, .2f, .2f, 1.0f));
	prime_ContextSetVsync(context, true);

	float vertices[] = {
		-0.5f, -0.5f, // left  
		 0.5f, -0.5f, // right 
		 0.0f,  0.5f // top   
	};

	u32 indices[] = { 0, 1, 2 };

	prime_BufferLayout* layout = prime_BufferLayoutCreate();
	prime_BufferElementAdd(layout, prime_BufferElementCreate(prime_DataTypeFloat2));

	prime_Vertexbuffer* vertexbuffer = prime_VertexbufferCreate(
		device,
		nullptr,
		sizeof(vertices),
		prime_VertexbufferTypeDynamic
	);

	prime_BufferLayoutSet(vertexbuffer, layout);

	prime_Indexbuffer* indexbuffer = prime_IndexbufferCreate(
		device, indices, 3);

	prime_VertexbufferSetData(vertexbuffer, vertices, sizeof(vertices));

	prime_Shader* shader = prime_ShaderCreate(device, 
		"shaders/gl_vertex_shader.glsl",
		"shaders/gl_fragment_shader.glsl");

	prime_ShaderBind(shader);

	while (!prime_WindowShouldClose(window)) {

		prime_WindowPollEvents();

		prime_ContextClear(context);
		prime_ContextDrawIndexed(context, prime_DrawModeTriangles, 3);
		prime_ContextSwapbuffers(context);
	}

	prime_BufferLayoutDestroy(layout);
	prime_DeviceDestroy(device);
	prime_WindowDestroy(window);


	prime_LogInfo("End Shader Test GL");
	prime_LogInfo("");
	return PRIME_PASSED;
}