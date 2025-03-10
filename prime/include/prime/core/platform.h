
#pragma once

#include "prime/defines.h"
#include "scope.h"
#include "prime/core/window.h"
#include "prime/renderer/renderer_API.h"

namespace prime::core {

    class Platform
    {
    public:
        static i32 init();
        static void shutdown();

        static void setUserData(void* pointer);
        static void* getUserData();

        static Scope<Window> createWindow(const str& title, u32 width, u32 height);
        static Scope<renderer::RendererAPI> createAPI(GraphicsAPI API, const Scope<Window>& window);
    };
    
} // namespace prime::core
