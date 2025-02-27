
#pragma once

#include "defines.h"
#include "device.h"

namespace prime {
    
    class Platform
    {
    public:
        static b8 
        init();

        static void 
        shutdown();

        static Ref<Device> 
        createDevice(DeviceType type, const Window& window);
    };

} // namespace prime
