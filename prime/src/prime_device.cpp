
#include "prime/prime_device.h"
#include "prime/prime_memory.h"
#include "prime/prime_context.h"
#include "prime_utils.h"

#include <map>
#include <vector>
#include <algorithm>

struct primeDevice
{
	u32 id = 0;
	primeDeviceType type;
};

struct Data
{
    u32 index = 1;
    std::map<u32, std::vector<primeContext*>> contexts;
};

static Data s_Data;

primeDevice*
primeDeviceCreate(primeDeviceType device_type)
{
	primeDevice* device = (primeDevice*)primeMemoryAlloc(sizeof(primeDevice));
	device->type = device_type;
	device->id = s_Data.index;
	s_Data.index++;
	return device;
}

void
primeDeviceDestroy(primeDevice* device)
{
	PASSERT_MSG(device, "Device is null");

	// contexts
	auto& contexts = s_Data.contexts[device->id];
	for (primeContext* context : contexts) {
		primeContextDestroy(context);
	}

	s_Data.contexts[device->id].clear();
	
	device->id = 0;
	s_Data.index--;
	primeMemoryFree(device, sizeof(primeDevice));
}

primeDeviceType
primeDeviceGetType(primeDevice* device)
{
	PASSERT_MSG(device, "Device is null");
	return device->type;
}

void
primeDeviceAppendContext(primeDevice* device, primeContext* context)
{
	s_Data.contexts[device->id].push_back(context);
}

void
primeDevicePopContext(primeDevice* device, primeContext* context)
{
	auto& contexts = s_Data.contexts[device->id];

	auto it = std::find(contexts.begin(), contexts.end(), context);
	if (it != contexts.end())
	{
		contexts.erase(it);
	}
}

