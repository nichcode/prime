
#include "prime/device.h"
#include "prime/logger.h"
#include "opengl/opengl_context.h"

#include <algorithm>

namespace prime {

    void 
    Device::append(Context* context)
    {
        m_Contexts.push_back(context);
    }

    void 
    Device::pop(Context* context)
    {
        auto it = std::find(m_Contexts.begin(), m_Contexts.end(), context);
        if (it != m_Contexts.end())
        {
            m_Contexts.erase(it);
        }
    }

    void 
    Device::init(DeviceType type)
    {
        m_Type = type;
        m_Contexts.clear();
    }

    void 
    Device::destroy()
    {
        m_Type = DeviceType::None;
        for (Context* context : m_Contexts) {
            destroyContext(context);
        }

        m_Contexts.clear();
    }

    Context* 
    Device::createContext(const Window& window)
    {
        switch (m_Type)
        {
            case DeviceType::OpenGL: {
                Context* context = new GLContext(window);
                append(context);
                return context;
            }
            break;
        }
        return nullptr;
    }

    void 
    Device::destroyContext(Context* context)
    {
        PASSERT_MSG(context, "context is null");
        auto it = std::find(m_Contexts.begin(), m_Contexts.end(), context);
        if (it != m_Contexts.end())
        {
            m_Contexts.erase(it);
        }

        delete context;
    }
    
} // namespace prime
