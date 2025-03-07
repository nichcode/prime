
#include "prime/renderer/context.h"
#include "opengl/gl_context.h"

namespace prime::renderer {

    core::Scope<Context> Context::create(GraphicsAPI API, const core::Window& window)
    {
        switch (API)
        {
        case GraphicsAPIGL:
            return core::createScope<GLContext>(API, window);
            break;
        }
        return nullptr;
    }
    
} // namespace prime::renderer
