
#include "tests.h"

b8
staticBufferTestGL()
{
	prime_LogInfo("");
	prime_LogInfo("Begin Static Buffer Test GL");

	prime_Device* device = prime_CreateDevice(prime_DeviceTypeGL);
	prime_Window* window = prime_CreateWindow("Begin Static Buffer Test GL", 640, 480);
	prime_Context* context = prime_CreateContext(device, window);
	prime_MakeActive(context);
	prime_SetClearColor(context, prime_ColorFromF32(.2f, .2f, .2f, 1.0f));
	prime_SetVsync(context, true);

	float vertices[] = {
		-0.5f, -0.5f, 0.0f, // left  
		 0.5f, -0.5f, 0.0f, // right 
		 0.0f,  0.5f, 0.0f  // top   
	};

	u32 indices[] = { 0, 1, 2 };

	prime_BufferLayout* layout = prime_CreateBufferLayout();
	prime_AddBufferElement(layout, prime_CreateBufferElement(prime_BufferDataTypeFloat3));

	prime_Vertexbuffer* vertexbuffer = prime_CreateVertexbuffer(
		device,
		vertices,
		sizeof(vertices),
		prime_VertexbufferTypeStatic
	);

	prime_SetBufferLayout(vertexbuffer, layout);

	prime_Indexbuffer* indexbuffer = prime_CreateIndexbuffer(
		device, indices, 3);

	while (!prime_WindowShouldClose(window)) {

		prime_PollEvents();

		prime_Clear(context);
		prime_DrawIndexed(context, prime_TopologyTriangles, 3);
		prime_Swapbuffers(context);
	}

	prime_DestroyBufferLayout(layout);
	prime_DestroyDevice(device);
	prime_DestroyWindow(window);

	prime_LogInfo("End Static Buffer Test GL");
	prime_LogInfo("");
	return PRIME_PASSED;
}

b8
dynamicBufferTestGL()
{
	prime_LogInfo("");
	prime_LogInfo("Begin Dynamic Buffer Test GL");

	prime_Device* device = prime_CreateDevice(prime_DeviceTypeGL);
	prime_Window* window = prime_CreateWindow("Begin Dynamic Buffer Test GL", 640, 480);
	prime_Context* context = prime_CreateContext(device, window);
	prime_MakeActive(context);
	prime_SetClearColor(context, prime_ColorFromF32(.2f, .2f, .2f, 1.0f));
	prime_SetVsync(context, true);

	float vertices[] = {
		-0.5f, -0.5f, 0.0f, // left  
		 0.5f, -0.5f, 0.0f, // right 
		 0.0f,  0.5f, 0.0f  // top   
	};

	u32 indices[] = { 0, 1, 2 };

	prime_BufferLayout* layout = prime_CreateBufferLayout();
	prime_AddBufferElement(layout, prime_CreateBufferElement(prime_BufferDataTypeFloat3));

	prime_Vertexbuffer* vertexbuffer = prime_CreateVertexbuffer(
		device,
		nullptr,
		sizeof(vertices),
		prime_VertexbufferTypeDynamic
	);

	prime_SetBufferLayout(vertexbuffer, layout);

	prime_Indexbuffer* indexbuffer = prime_CreateIndexbuffer(
		device, indices, 3);

	prime_SetVertexbufferData(vertexbuffer, vertices, sizeof(vertices));

	while (!prime_WindowShouldClose(window)) {

		prime_PollEvents();

		prime_Clear(context);
		prime_DrawIndexed(context, prime_TopologyTriangles, 3);
		prime_Swapbuffers(context);
	}

	prime_DestroyBufferLayout(layout);
	prime_DestroyDevice(device);
	prime_DestroyWindow(window);


	prime_LogInfo("Begin Dynamic Buffer Test GL");
	prime_LogInfo("");
	return PRIME_PASSED;
}
