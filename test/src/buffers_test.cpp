
#include "tests.h"

b8
staticBufferTestGL()
{
	prime_LogInfo("");
	prime_LogInfo("Begin Static Buffer Test GL");

	prime_Device* device = prime_DeviceCreate(prime_DeviceTypeGL);
	prime_Window* window = prime_WindowCreate("Begin Static Buffer Test GL", 640, 480);
	prime_Context* context = prime_ContextCreate(device, window);
	prime_ContextMakeActive(context);
	prime_ContextSetClearColor(context, prime_ColorFromF32(.2f, .2f, .2f, 1.0f));
	prime_ContextSetVsync(context, true);

	float vertices[] = {
		-0.5f, -0.5f, 0.0f, // left  
		 0.5f, -0.5f, 0.0f, // right 
		 0.0f,  0.5f, 0.0f  // top   
	};

	u32 indices[] = { 0, 1, 2 };

	prime_BufferLayout* layout = prime_BufferLayoutCreate();
	prime_BufferElementAdd(layout, prime_BufferElementCreate(prime_DataTypeFloat3));

	prime_Vertexbuffer* vertexbuffer = prime_VertexbufferCreate(
		device,
		vertices,
		sizeof(vertices),
		prime_VertexbufferTypeStatic
	);

	prime_BufferLayoutSet(vertexbuffer, layout);

	prime_Indexbuffer* indexbuffer = prime_IndexbufferCreate(
		device, indices, 3);

	while (!prime_WindowShouldClose(window)) {

		prime_WindowPollEvents();

		prime_ContextClear(context);
		prime_ContextDrawIndexed(context, prime_DrawModeTriangles, 3);
		prime_ContextSwapbuffers(context);
	}

	prime_BufferLayoutDestroy(layout);
	prime_DeviceDestroy(device);
	prime_WindowDestroy(window);

	prime_LogInfo("End Static Buffer Test GL");
	prime_LogInfo("");
	return PRIME_PASSED;
}

b8
dynamicBufferTestGL()
{
	prime_LogInfo("");
	prime_LogInfo("Begin Dynamic Buffer Test GL");

	prime_Device* device = prime_DeviceCreate(prime_DeviceTypeGL);
	prime_Window* window = prime_WindowCreate("Begin Dynamic Buffer Test GL", 640, 480);
	prime_Context* context = prime_ContextCreate(device, window);
	prime_ContextMakeActive(context);
	prime_ContextSetClearColor(context, prime_ColorFromF32(.2f, .2f, .2f, 1.0f));
	prime_ContextSetVsync(context, true);

	float vertices[] = {
		-0.5f, -0.5f, 0.0f, // left  
		 0.5f, -0.5f, 0.0f, // right 
		 0.0f,  0.5f, 0.0f  // top   
	};

	u32 indices[] = { 0, 1, 2 };

	prime_BufferLayout* layout = prime_BufferLayoutCreate();
	prime_BufferElementAdd(layout, prime_BufferElementCreate(prime_DataTypeFloat3));

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

	while (!prime_WindowShouldClose(window)) {

		prime_WindowPollEvents();

		prime_ContextClear(context);
		prime_ContextDrawIndexed(context, prime_DrawModeTriangles, 3);
		prime_ContextSwapbuffers(context);
	}

	prime_BufferLayoutDestroy(layout);
	prime_DeviceDestroy(device);
	prime_WindowDestroy(window);


	prime_LogInfo("Begin Dynamic Buffer Test GL");
	prime_LogInfo("");
	return PRIME_PASSED;
}
