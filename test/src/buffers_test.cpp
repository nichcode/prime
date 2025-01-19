
#include "tests.h"

b8
staticVertexbufferTestGL()
{
	prime_LogInfo("");
	prime_LogInfo("Begin Static Vertexbuffer Test GL");

	prime_Device* device = prime_CreateDevice(prime_DeviceTypeGL);

	float vertices[] = {
		-0.5f, -0.5f, 0.0f, // left  
		 0.5f, -0.5f, 0.0f, // right 
		 0.0f,  0.5f, 0.0f  // top   
	};

	prime_BufferLayout* layout = prime_CreateBufferLayout();
	prime_AddBufferElement(layout, prime_CreateBufferElement(prime_BufferDataTypeFloat3));

	prime_Vertexbuffer* vertexbuffer = prime_CreateVertexbuffer(
		device,
		vertices,
		sizeof(vertices),
		prime_VertexbufferTypeStatic
	);

	prime_SetBufferLayout(vertexbuffer, layout);
	prime_SetVertexbufferData(vertexbuffer, vertices, sizeof(vertices));

	prime_DestroyBufferLayout(layout);
	prime_DestroyDevice(device);

	prime_LogInfo("End Dynamic Vertexbuffer Test GL");
	prime_LogInfo("");
	return PRIME_PASSED;
}

b8
dynamicVertexbufferTestGL()
{
	prime_LogInfo("");
	prime_LogInfo("Begin Renderer2D Test GL");

	prime_Device* device = prime_CreateDevice(prime_DeviceTypeGL);

	float vertices[] = {
		-0.5f, -0.5f, 0.0f, // left  
		 0.5f, -0.5f, 0.0f, // right 
		 0.0f,  0.5f, 0.0f  // top   
	};

	prime_BufferLayout* layout = prime_CreateBufferLayout();
	prime_AddBufferElement(layout, prime_CreateBufferElement(prime_BufferDataTypeFloat3));

	prime_Vertexbuffer* vertexbuffer = prime_CreateVertexbuffer(
		device,
		nullptr,
		sizeof(vertices),
		prime_VertexbufferTypeDynamic
	);

	prime_SetBufferLayout(vertexbuffer, layout);
	prime_SetVertexbufferData(vertexbuffer, vertices, sizeof(vertices));

	prime_DestroyBufferLayout(layout);
	prime_DestroyDevice(device);


	prime_LogInfo("End Renderer2D Test GL");
	prime_LogInfo("");
	return PRIME_PASSED;
}