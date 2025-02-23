
#pragma once

#include "context.h"

#include <vector>

namespace prime {

    enum class DeviceType
    {
        OpenGL
    };

    class Device
    {
    private:
        DeviceType m_Type;
        std::vector<Context*> m_Contexts;

    public:
        ~Device()
        {
            destroy();
        }

        void 
        init(DeviceType type);

        void 
        destroy();

        Context* 
        createContext(const Window& window);

        void 
        destroyContext(Context* context);
    };
    
} // namespace prime
