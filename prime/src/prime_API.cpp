
#include "pch.h"
#include "prime_API.h"

#include "opengl/opengl_context.h"

#ifdef PRIME_PLATFORM_WINDOWS
#include "windows/windows_API.h"
#endif // PRIME_PLATFORM_WINDOWS

void prime_InitAPI()
{
#ifdef PRIME_PLATFORM_WINDOWS
    windows_PlatformInit();
#endif // PRIME_PLATFORM_WINDOWS

    switch (s_Data.type) {
        case PRIME_DEVICE_OPENGL: {
            s_Data.api.createContext = gl_CreateContext;
            s_Data.api.clear = gl_Clear;
            s_Data.api.destroyContext = gl_DestroyContext;
            s_Data.api.makeActive = gl_MakeActive;
            s_Data.api.swapBuffers = gl_SwapBuffers;
            s_Data.api.setVsync = gl_SetVsync;
            s_Data.api.setClearColor = gl_SetClearColor;

            break;
        }
    }
}

void prime_ShutdownAPI()
{
#ifdef PRIME_PLATFORM_WINDOWS
    windows_PlatformShutdown();
#endif // PRIME_PLATFORM_WINDOWS
}
