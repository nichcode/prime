
#include "prime/prime_buffers.h"
#include "prime/prime_memory.h"
#include "prime/prime_log.h"
#include "prime_utils.h"

#include "opengl/opengl_buffers.h"

#include "map"
#include <vector>

static u32 s_IDIndex = 1;
static std::map<u32, std::vector<prime_BufferElement>> s_BufferElements;

struct prime_BufferLayout
{
	u32 id = 0;
	u32 stride;
};

struct prime_Vertexbuffer
{
	prime_VertexbufferType type;
	prime_BufferLayout* layout = nullptr;
	prime_VertexbufferHandle* handle = nullptr;

	void(*destroyFunc)(prime_VertexbufferHandle* handle);
	void(*bindFunc)(prime_VertexbufferHandle* handle);
	void(*unbindFunc)(prime_VertexbufferHandle* handle);
	void(*setLayoutFunc)(const prime_BufferElement* element, u32 stride);
	void(*setDataFunc)(prime_VertexbufferHandle* handle, const void* data, u32 size);
};

prime_BufferLayout*
prime_CreateBufferLayout()
{
	prime_BufferLayout* layout = nullptr;
	layout = (prime_BufferLayout*)prime_MemAlloc(sizeof(prime_BufferLayout));
	PRIME_ASSERT_MSG(layout, "prime_BufferLayout creation failed");
	layout->id = s_IDIndex;
	s_IDIndex++;
	return layout;
}

void
prime_DestroyBufferLayout(prime_BufferLayout* layout)
{
	PRIME_ASSERT_MSG(layout, "layout is null");
	s_BufferElements[layout->id].clear();
	layout->id = 0;
	prime_MemFree(layout, sizeof(prime_BufferLayout));
	s_IDIndex--;
}

void
prime_AddBufferElement(prime_BufferLayout* layout, const prime_BufferElement& element)
{
	PRIME_ASSERT_MSG(layout, "layout is null");
	s_BufferElements[layout->id].push_back(element);
}

prime_Vertexbuffer*
prime_CreateVertexbuffer(prime_Device* device, const void* data, u32 size, prime_VertexbufferType type)
{
	PRIME_ASSERT_MSG(device, "Device is null");
	prime_Vertexbuffer* vertexbuffer = (prime_Vertexbuffer*)prime_MemAlloc(sizeof(prime_Vertexbuffer));
	vertexbuffer->type = type;

	switch (prime_GetDeviceType(device))
	{
#ifdef PRIME_PLATFORM_WINDOWS
	case prime_DeviceTypeDx11: {
		PRIME_ASSERT_MSG(false, "Dx11 vertexbuffer not implemented yet");
		break;
	}
#endif // PRIME_PLATFORM_WINDOWS

	case prime_DeviceTypeGL: {
		vertexbuffer->handle = prime_GLCreateVertexbufferHandle(data, size, type);

		// function ppinters
		vertexbuffer->bindFunc = prime_GLBindVertexbufferHandle;
		vertexbuffer->destroyFunc = prime_GLDestroyVertexbufferHandle;
		vertexbuffer->setDataFunc = prime_GLSetVertexbufferHandleData;
		vertexbuffer->setLayoutFunc = prime_GLSetVertexbufferLayout;
		vertexbuffer->unbindFunc = prime_GLUnbindVertexbufferHandle;

		break;
	}

	}
	return vertexbuffer;
}

void
prime_DestroyVertexbuffer(prime_Vertexbuffer* vertexbuffer)
{
	PRIME_ASSERT_MSG(vertexbuffer, "vertexbuffer is null");
	vertexbuffer->destroyFunc(vertexbuffer->handle);

	vertexbuffer->bindFunc = nullptr;
	vertexbuffer->destroyFunc = nullptr;
	vertexbuffer->setDataFunc = nullptr;
	vertexbuffer->setLayoutFunc = nullptr;
	vertexbuffer->unbindFunc = nullptr;
	prime_MemFree(vertexbuffer, sizeof(prime_Vertexbuffer));
}

void
prime_SetBufferLayout(prime_Vertexbuffer* vertexbuffer, prime_BufferLayout* layout)
{
	PRIME_ASSERT_MSG(vertexbuffer, "vertexbuffer is null");
	layout->stride = 0;
	for (auto& element : s_BufferElements[layout->id])
	{
		element.offset = layout->stride;
		layout->stride += element.size;
	}

	for (const auto& element : s_BufferElements[layout->id]) {
		vertexbuffer->setLayoutFunc(&element, layout->stride);
	}
}

void
prime_BindVertexbuffer(prime_Vertexbuffer* vertexbuffer)
{
	PRIME_ASSERT_MSG(vertexbuffer, "vertexbuffer is null");
	vertexbuffer->bindFunc(vertexbuffer->handle);
}

void
prime_UnbindVertexbuffer(prime_Vertexbuffer* vertexbuffer)
{
	PRIME_ASSERT_MSG(vertexbuffer, "vertexbuffer is null");
	vertexbuffer->unbindFunc(vertexbuffer->handle);
}

prime_VertexbufferType
prime_GetVertexbufferType(prime_Vertexbuffer* vertexbuffer)
{
	PRIME_ASSERT_MSG(vertexbuffer, "vertexbuffer is null");
	return vertexbuffer->type;
}

prime_BufferLayout*
prime_GetBufferLayout(prime_Vertexbuffer* vertexbuffer)
{
	PRIME_ASSERT_MSG(vertexbuffer, "vertexbuffer is null");
	return vertexbuffer->layout;
}

void
prime_SetVertexbufferData(prime_Vertexbuffer* vertexbuffer, const void* data, u32 size)
{
	PRIME_ASSERT_MSG(vertexbuffer, "vertexbuffer is null");
	if (vertexbuffer->type == prime_VertexbufferTypeDynamic) {
		vertexbuffer->setDataFunc(vertexbuffer->handle, data, size);
	}
	else {
		PRIME_WARN("Cannot set data to a static vertexbuffer.");
	}
}