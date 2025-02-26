
#pragma once

#include "context.h"

namespace prime {

    enum class DeviceType
    {
        OpenGL
    };

    class Device
    {
    private:
        DeviceType m_Type;

    public:
        void 
        init(DeviceType type);

        Ref<Context> 
        createContext(const Window& window);
    };
    
} // namespace prime
