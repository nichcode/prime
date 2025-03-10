
#include "prime/core/platform.h"
#include "windows/windows_window.h"

#include "opengl/gl_renderer_API.h"

static void* s_UserData = nullptr;

namespace prime::core {

    Scope<Window> Platform::createWindow(const str& title, u32 width, u32 height)
    {
        return createScope<WindowsWindow>(title, width, height);
    }

    Scope<renderer::RendererAPI> Platform::createAPI(GraphicsAPI API, const Scope<Window>& window)
    {
        switch (API)
        {
        case GraphicsAPIGL:
            return createScope<renderer::GLRendererAPI>(window);
            break;

        }
        return nullptr;
    }

    void Platform::setUserData(void* pointer)
    {
        s_UserData = pointer;
    }

    void* Platform::getUserData()
    {
        return s_UserData;
    }
    
} // namespace prime::core
