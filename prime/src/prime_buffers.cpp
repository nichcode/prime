
#include "prime/prime_buffers.h"
#include "prime/prime_memory.h"
#include "prime/prime_log.h"
#include "prime/prime_device.h"
#include "prime_utils.h"

#include "opengl/prime_opengl_buffers.h"

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
	prime_Device* device = nullptr;
	prime_VertexbufferType type;
	prime_BufferLayout* layout = nullptr;
	void* handle = nullptr;

	void(*destroyFunc)(void* handle);
	void(*bindFunc)(void* handle);
	void(*unbindFunc)(void* handle);
	void(*setLayoutFunc)(void* handle, const prime_BufferElement* element, u32 stride);
	void(*setDataFunc)(void* handle, const void* data, u32 size);
};

struct prime_Indexbuffer
{
	u32 count = 0;
	prime_Device* device = nullptr;
	void* handle = nullptr;

	void(*destroyFunc)(void* handle);
	void(*bindFunc)(void* handle);
	void(*unbindFunc)(void* handle);
};

prime_BufferLayout*
prime_BufferLayoutCreate()
{
	prime_BufferLayout* layout = nullptr;
	layout = (prime_BufferLayout*)prime_MemAlloc(sizeof(prime_BufferLayout));
	PRIME_ASSERT_MSG(layout, "prime_BufferLayout creation failed");
	layout->id = s_IDIndex;
	s_IDIndex++;
	return layout;
}

void
prime_BufferLayoutDestroy(prime_BufferLayout* layout)
{
	PRIME_ASSERT_MSG(layout, "layout is null");
	s_BufferElements[layout->id].clear();
	layout->id = 0;
	prime_MemFree(layout, sizeof(prime_BufferLayout));
	s_IDIndex--;
}

void
prime_BufferElementAdd(prime_BufferLayout* layout, const prime_BufferElement& element)
{
	PRIME_ASSERT_MSG(layout, "layout is null");
	s_BufferElements[layout->id].push_back(element);
}

prime_Vertexbuffer*
prime_VertexbufferCreate(prime_Device* device, const void* data, u32 size, prime_VertexbufferType type)
{
	PRIME_ASSERT_MSG(device, "Device is null");
	prime_Vertexbuffer* vertexbuffer = (prime_Vertexbuffer*)prime_MemAlloc(sizeof(prime_Vertexbuffer));
	vertexbuffer->type = type;
	vertexbuffer->device = device;

	switch (prime_DeviceGetType(device))
	{
#ifdef PRIME_PLATFORM_WINDOWS
	case prime_DeviceTypeDx11: {
		PRIME_ASSERT_MSG(false, "Dx11 vertexbuffer not implemented yet");
		break;
	}
#endif // PRIME_PLATFORM_WINDOWS

	case prime_DeviceTypeGL: {
		vertexbuffer->handle = gl_CreateVertexbuffer(data, size, type);

		// function ppinters
		vertexbuffer->bindFunc = gl_BindVertexbuffer;
		vertexbuffer->destroyFunc = gl_DestroyVertexbuffer;
		vertexbuffer->setDataFunc = gl_SetVertexbufferData;
		vertexbuffer->setLayoutFunc = gl_SetVertexbufferLayout;
		vertexbuffer->unbindFunc = gl_UnbindVertexbuffer;

		break;
	}

	}
	appendVertexbuffer(device, vertexbuffer);
	return vertexbuffer;
}

void
prime_VertexbufferDestroy(prime_Vertexbuffer* vertexbuffer)
{
	PRIME_ASSERT_MSG(vertexbuffer, "vertexbuffer is null");
	vertexbuffer->destroyFunc(vertexbuffer->handle);

	vertexbuffer->bindFunc = nullptr;
	vertexbuffer->destroyFunc = nullptr;
	vertexbuffer->setDataFunc = nullptr;
	vertexbuffer->setLayoutFunc = nullptr;
	vertexbuffer->unbindFunc = nullptr;
	popVertexbuffer(vertexbuffer->device, vertexbuffer);
	vertexbuffer->device = nullptr;
	prime_MemFree(vertexbuffer, sizeof(prime_Vertexbuffer));
}

void
prime_BufferLayoutSet(prime_Vertexbuffer* vertexbuffer, prime_BufferLayout* layout)
{
	PRIME_ASSERT_MSG(vertexbuffer, "vertexbuffer is null");
	layout->stride = 0;
	for (auto& element : s_BufferElements[layout->id])
	{
		element.offset = layout->stride;
		layout->stride += element.size;
	}

	for (const auto& element : s_BufferElements[layout->id]) {
		vertexbuffer->setLayoutFunc(vertexbuffer->handle, &element, layout->stride);
	}
}

void
prime_VertexbufferBind(prime_Vertexbuffer* vertexbuffer)
{
	PRIME_ASSERT_MSG(vertexbuffer, "vertexbuffer is null");
	vertexbuffer->bindFunc(vertexbuffer->handle);
}

void
prime_VertexbufferUnbind(prime_Vertexbuffer* vertexbuffer)
{
	PRIME_ASSERT_MSG(vertexbuffer, "vertexbuffer is null");
	vertexbuffer->unbindFunc(vertexbuffer->handle);
}

prime_VertexbufferType
prime_VertexbufferGetType(prime_Vertexbuffer* vertexbuffer)
{
	PRIME_ASSERT_MSG(vertexbuffer, "vertexbuffer is null");
	return vertexbuffer->type;
}

prime_BufferLayout*
prime_BufferLayoutGet(prime_Vertexbuffer* vertexbuffer)
{
	PRIME_ASSERT_MSG(vertexbuffer, "vertexbuffer is null");
	return vertexbuffer->layout;
}

void
prime_VertexbufferSetData(prime_Vertexbuffer* vertexbuffer, const void* data, u32 size)
{
	PRIME_ASSERT_MSG(vertexbuffer, "vertexbuffer is null");
	if (vertexbuffer->type == prime_VertexbufferTypeDynamic) {
		vertexbuffer->setDataFunc(vertexbuffer->handle, data, size);
	}
	else {
		PRIME_WARN("Cannot set data to a static vertexbuffer.");
	}
}

prime_Indexbuffer* 
prime_IndexbufferCreate(prime_Device* device, u32* indices, u32 count)
{
	PRIME_ASSERT_MSG(device, "Device is null");
	prime_Indexbuffer* indexbuffer = (prime_Indexbuffer*)prime_MemAlloc(sizeof(prime_Indexbuffer));
	indexbuffer->device = device;
	indexbuffer->count = count;

	switch (prime_DeviceGetType(device))
	{
#ifdef PRIME_PLATFORM_WINDOWS
	case prime_DeviceTypeDx11: {
		PRIME_ASSERT_MSG(false, "Dx11 indexbuffer not implemented yet");
		break;
	}
#endif // PRIME_PLATFORM_WINDOWS

	case prime_DeviceTypeGL: {
		indexbuffer->handle = gl_CreateIndexbuffer(indices, count);

		// function ppinters
		indexbuffer->bindFunc = gl_BindIndexbuffer;
		indexbuffer->destroyFunc = gl_DestroyIndexbuffer;
		indexbuffer->unbindFunc = gl_UnbindIndexbuffer;

		break;
	}

	}
	appendIndexbuffer(device, indexbuffer);
	return indexbuffer;
}

void
prime_IndexbufferDestroy(prime_Indexbuffer* indexbuffer)
{
	PRIME_ASSERT_MSG(indexbuffer, "indexbuffer is null");
	indexbuffer->destroyFunc(indexbuffer->handle);

	indexbuffer->bindFunc = nullptr;
	indexbuffer->destroyFunc = nullptr;
	indexbuffer->unbindFunc = nullptr;
	popIndexbuffer(indexbuffer->device, indexbuffer);
	indexbuffer->device = nullptr;
	prime_MemFree(indexbuffer, sizeof(prime_Indexbuffer));
}

void 
prime_IndexbufferBind(prime_Indexbuffer* indexbuffer)
{
	PRIME_ASSERT_MSG(indexbuffer, "indexbuffer is null");
	indexbuffer->bindFunc(indexbuffer->handle);
}

void 
prime_IndexbufferUnbind(prime_Indexbuffer* indexbuffer)
{
	PRIME_ASSERT_MSG(indexbuffer, "indexbuffer is null");
	indexbuffer->unbindFunc(indexbuffer->handle);
}

u32 
prime_IndexbufferGetCount(prime_Indexbuffer* indexbuffer)
{
	PRIME_ASSERT_MSG(indexbuffer, "indexbuffer is null");
	return indexbuffer->count;
}
