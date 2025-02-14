
#include "prime/prime_device.h"
#include "prime/prime_memory.h"
#include "prime/prime_context.h"
#include "prime/prime_layout.h"
#include "prime_utils.h"

#include <map>
#include <vector>
#include <algorithm>

struct primeDevice
{
	u32 id = 0;
	primeDeviceType type;
};

struct DeviceData
{
    u32 index = 1;
    std::map<u32, std::vector<primeContext*>> contexts;
    std::map<u32, std::vector<primeLayout*>> layouts;
};

static DeviceData s_DeviceData;

primeDevice*
primeDeviceCreate(primeDeviceType device_type)
{
	primeDevice* device = (primeDevice*)primeMemoryAlloc(sizeof(primeDevice));
	device->type = device_type;
	device->id = s_DeviceData.index;
	s_DeviceData.index++;
	return device;
}

void
primeDeviceDestroy(primeDevice* device)
{
	PASSERT_MSG(device, "Device is null");

	// contexts
	auto& contexts = s_DeviceData.contexts[device->id];
	for (primeContext* context : contexts) {
		primeContextDestroy(context);
	}

	// layouts
	auto& layouts = s_DeviceData.layouts[device->id];
	for (primeLayout* layout : layouts) {
		primeLayoutDestroy(layout);
	}

	s_DeviceData.contexts[device->id].clear();
	s_DeviceData.layouts[device->id].clear();
	
	device->id = 0;
	s_DeviceData.index--;
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
	s_DeviceData.contexts[device->id].push_back(context);
}

void
primeDevicePopContext(primeDevice* device, primeContext* context)
{
	auto& contexts = s_DeviceData.contexts[device->id];

	auto it = std::find(contexts.begin(), contexts.end(), context);
	if (it != contexts.end())
	{
		contexts.erase(it);
	}
}

void
primeDeviceAppendLayout(primeDevice* device, primeLayout* layout)
{
	s_DeviceData.layouts[device->id].push_back(layout);
}

void
primeDevicePopLayout(primeDevice* device, primeLayout* layout)
{
	auto& layouts = s_DeviceData.layouts[device->id];

	auto it = std::find(layouts.begin(), layouts.end(), layout);
	if (it != layouts.end())
	{
		layouts.erase(it);
	}
}
