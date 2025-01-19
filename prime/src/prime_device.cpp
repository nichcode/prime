
#include "prime/prime_device.h"
#include "prime/prime_memory.h"
#include "prime/prime_log.h"
#include "prime/prime_context.h"
#include "prime_utils.h"

#include <map>
#include <vector>

static u32 s_IDIndex = 1;
static std::map<u32, std::vector<prime_Context*>> s_DeviceContexts;

struct prime_Device
{
	u32 id = 0;
	prime_Context* active_context;
	prime_DeviceType type;
};

prime_Device*
prime_CreateDevice(prime_DeviceType device_type)
{
	prime_Device* device = (prime_Device*)prime_MemAlloc(sizeof(prime_Device));
	device->type = device_type;
	device->id = s_IDIndex;
	s_IDIndex++;
	return device;
}

void
prime_DestroyDevice(prime_Device* device)
{
	PRIME_ASSERT_MSG(device, "Device is null");
	auto& device_contexts = s_DeviceContexts[device->id];
	for (prime_Context* context : device_contexts) {
		prime_DestroyContext(context);
	}

	s_DeviceContexts[device->id].clear();
	device->id = 0;
	s_IDIndex--;
	prime_MemFree(device, sizeof(prime_Device));
}

prime_DeviceType
prime_GetDeviceType(prime_Device* device)
{
	PRIME_ASSERT_MSG(device, "Device is null");
	return device->type;
}

void
prime_AddContext(prime_Device* device, prime_Context* context)
{
	s_DeviceContexts[device->id].push_back(context);
}

void
prime_RemoveContext(prime_Device* device, prime_Context* context)
{
	auto& device_contexts = s_DeviceContexts[device->id];

	auto it = std::find(device_contexts.begin(), device_contexts.end(), context);
	if (it != device_contexts.end())
	{
		device_contexts.erase(it);
	}
}