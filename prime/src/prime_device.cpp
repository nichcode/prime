
#include "prime/prime_device.h"
#include "prime/prime_memory.h"
#include "prime/prime_log.h"
#include "prime/prime_context.h"
#include "prime/prime_buffers.h"
#include "prime_utils.h"

#include <map>
#include <vector>

static u32 s_IDIndex = 1;
static std::map<u32, std::vector<prime_Context*>> s_DeviceContexts;
static std::map<u32, std::vector<prime_Vertexbuffer*>> s_DeviceVertexbuffers;
static std::map<u32, std::vector<prime_Indexbuffer*>> s_DeviceIndexbuffers;

struct prime_Device
{
	u32 id = 0;
	prime_DeviceType type;
};

prime_Device*
prime_DeviceCreate(prime_DeviceType device_type)
{
	prime_Device* device = (prime_Device*)prime_MemAlloc(sizeof(prime_Device));
	device->type = device_type;
	device->id = s_IDIndex;
	s_IDIndex++;
	return device;
}

void
prime_DeviceDestroy(prime_Device* device)
{
	PRIME_ASSERT_MSG(device, "Device is null");
	// contexts
	auto& device_contexts = s_DeviceContexts[device->id];
	for (prime_Context* context : device_contexts) {
		prime_ContextDestroy(context);
	}

	// vertexbuffer
	auto& device_vertexbuffers = s_DeviceVertexbuffers[device->id];
	for (prime_Vertexbuffer* vertexbuffer : device_vertexbuffers) {
		prime_VertexbufferDestroy(vertexbuffer);
	}

	// indexbuffer
	auto& device_indexbuffers = s_DeviceIndexbuffers[device->id];
	for (prime_Indexbuffer* indexbuffer : device_indexbuffers) {
		prime_IndexbufferDestroy(indexbuffer);
	}

	s_DeviceContexts[device->id].clear();
	s_DeviceVertexbuffers[device->id].clear();
	s_DeviceIndexbuffers[device->id].clear();
	
	device->id = 0;
	s_IDIndex--;
	prime_MemFree(device, sizeof(prime_Device));
}

prime_DeviceType
prime_DeviceGetType(prime_Device* device)
{
	PRIME_ASSERT_MSG(device, "Device is null");
	return device->type;
}

void
appendContext(prime_Device* device, prime_Context* context)
{
	s_DeviceContexts[device->id].push_back(context);
}

void
popContext(prime_Device* device, prime_Context* context)
{
	auto& device_contexts = s_DeviceContexts[device->id];

	auto it = std::find(device_contexts.begin(), device_contexts.end(), context);
	if (it != device_contexts.end())
	{
		device_contexts.erase(it);
	}
}

void
appendVertexbuffer(prime_Device* device, prime_Vertexbuffer* vertexbuffer)
{
	s_DeviceVertexbuffers[device->id].push_back(vertexbuffer);
}

void
popVertexbuffer(prime_Device* device, prime_Vertexbuffer* vertexbuffer)
{
	auto& device_vertexbuffers = s_DeviceVertexbuffers[device->id];

	auto it = std::find(device_vertexbuffers.begin(), device_vertexbuffers.end(), vertexbuffer);
	if (it != device_vertexbuffers.end())
	{
		device_vertexbuffers.erase(it);
	}
}

void
appendIndexbuffer(prime_Device* device, prime_Indexbuffer* indexbuffer)
{
	s_DeviceIndexbuffers[device->id].push_back(indexbuffer);
}

void
popIndexbuffer(prime_Device* device, prime_Indexbuffer* indexbuffer)
{
	auto& device_indexbuffers = s_DeviceIndexbuffers[device->id];

	auto it = std::find(device_indexbuffers.begin(), device_indexbuffers.end(), indexbuffer);
	if (it != device_indexbuffers.end())
	{
		device_indexbuffers.erase(it);
	}
}