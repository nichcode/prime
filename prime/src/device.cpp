
#include "prime/device.h"
#include "prime/logger.h"

#include "opengl/opengl_context.h"

namespace prime {

    void 
    Device::init(DeviceType type)
    {
        m_Type = type;
    }

    Ref<Context> 
    Device::createContext(const Window& window)
    {
        switch (m_Type)
        {
            case DeviceType::OpenGL: {
                return createRef<GLContext>(window);
            }
            break;
        }
        return nullptr;
    }
    
} // namespace prime
