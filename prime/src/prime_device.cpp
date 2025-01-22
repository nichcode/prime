
#include "prime/prime_device.h"
#include "prime/prime_memory.h"
#include "prime/prime_log.h"
#include "prime/prime_context.h"
#include "prime/prime_buffers.h"
#include "prime/prime_shader.h"
#include "prime/prime_texture2d.h"
#include "prime_utils.h"

#include <map>
#include <vector>

struct Data
{
	u32 index = 1;
	std::map<u32, std::vector<prime_Context*>> contexts;
	std::map<u32, std::vector<prime_Vertexbuffer*>> vertexbuffers;
	std::map<u32, std::vector<prime_Indexbuffer*>> indexbuffers;
	std::map<u32, std::vector<prime_Shader*>> shaders;
	std::map<u32, std::vector<prime_Uniformbuffer*>> uniformbuffers;
	std::map<u32, std::vector<prime_Texture2D*>> texture2ds;
};

static Data s_Data;

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
	device->id = s_Data.index;
	s_Data.index++;
	return device;
}

void
prime_DeviceDestroy(prime_Device* device)
{
	PRIME_ASSERT_MSG(device, "Device is null");
	// contexts
	auto& contexts = s_Data.contexts[device->id];
	for (prime_Context* context : contexts) {
		prime_ContextDestroy(context);
	}

	// vertexbuffer
	auto& vertexbuffers = s_Data.vertexbuffers[device->id];
	for (prime_Vertexbuffer* vertexbuffer : vertexbuffers) {
		prime_VertexbufferDestroy(vertexbuffer);
	}

	// indexbuffer
	auto& indexbuffers = s_Data.indexbuffers[device->id];
	for (prime_Indexbuffer* indexbuffer : indexbuffers) {
		prime_IndexbufferDestroy(indexbuffer);
	}

	// shaders
	auto& shaders = s_Data.shaders[device->id];
	for (prime_Shader* shader : shaders) {
		prime_ShaderDestroy(shader);
	}

	// uniformbuffers
	auto& uniformbuffers = s_Data.uniformbuffers[device->id];
	for (prime_Uniformbuffer* uniformbuffer : uniformbuffers) {
		prime_UniformbufferDestroy(uniformbuffer);
	}

	s_Data.contexts[device->id].clear();
	s_Data.vertexbuffers[device->id].clear();
	s_Data.indexbuffers[device->id].clear();
	s_Data.shaders[device->id].clear();
	s_Data.uniformbuffers[device->id].clear();
	
	device->id = 0;
	s_Data.index--;
	prime_MemFree(device, sizeof(prime_Device));
}

prime_DeviceType
prime_DeviceGetType(prime_Device* device)
{
	PRIME_ASSERT_MSG(device, "Device is null");
	return device->type;
}

void
prime_AppendContext(prime_Device* device, prime_Context* context)
{
	s_Data.contexts[device->id].push_back(context);
}

void
prime_PopContext(prime_Device* device, prime_Context* context)
{
	auto& contexts = s_Data.contexts[device->id];

	auto it = std::find(contexts.begin(), contexts.end(), context);
	if (it != contexts.end())
	{
		contexts.erase(it);
	}
}

void
prime_AppendVertexbuffer(prime_Device* device, prime_Vertexbuffer* vertexbuffer)
{
	s_Data.vertexbuffers[device->id].push_back(vertexbuffer);
}

void
prime_PopVertexbuffer(prime_Device* device, prime_Vertexbuffer* vertexbuffer)
{
	auto& vertexbuffers = s_Data.vertexbuffers[device->id];

	auto it = std::find(vertexbuffers.begin(), vertexbuffers.end(), vertexbuffer);
	if (it != vertexbuffers.end())
	{
		vertexbuffers.erase(it);
	}
}

void
prime_AppendIndexbuffer(prime_Device* device, prime_Indexbuffer* indexbuffer)
{
	s_Data.indexbuffers[device->id].push_back(indexbuffer);
}

void
prime_PopIndexbuffer(prime_Device* device, prime_Indexbuffer* indexbuffer)
{
	auto& indexbuffers = s_Data.indexbuffers[device->id];

	auto it = std::find(indexbuffers.begin(), indexbuffers.end(), indexbuffer);
	if (it != indexbuffers.end())
	{
		indexbuffers.erase(it);
	}
}

void
prime_AppendShader(prime_Device* device, prime_Shader* shader)
{
	s_Data.shaders[device->id].push_back(shader);
}

void
prime_PopShader(prime_Device* device, prime_Shader* shader)
{
	auto& shaders = s_Data.shaders[device->id];

	auto it = std::find(shaders.begin(), shaders.end(), shader);
	if (it != shaders.end())
	{
		shaders.erase(it);
	}
}

void
prime_AppendUniformbuffer(prime_Device* device, prime_Uniformbuffer* uniformbuffer)
{
	s_Data.uniformbuffers[device->id].push_back(uniformbuffer);
}

void
prime_PopUniformbuffer(prime_Device* device, prime_Uniformbuffer* uniformbuffer)
{
	auto& uniformbuffers = s_Data.uniformbuffers[device->id];

	auto it = std::find(uniformbuffers.begin(), uniformbuffers.end(), uniformbuffer);
	if (it != uniformbuffers.end())
	{
		uniformbuffers.erase(it);
	}
}

void
prime_AppendTexture2D(prime_Device* device, prime_Texture2D* texture2d)
{
	s_Data.texture2ds[device->id].push_back(texture2d);
}

void
prime_PopTexture2D(prime_Device* device, prime_Texture2D* texture2d)
{
	auto& texture2ds = s_Data.texture2ds[device->id];

	auto it = std::find(texture2ds.begin(), texture2ds.end(), texture2d);
	if (it != texture2ds.end())
	{
		texture2ds.erase(it);
	}
}