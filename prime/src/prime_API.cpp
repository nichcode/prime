
#include "pch.h"
#include "prime_API.h"

#include "opengl/opengl_context.h"
#include "opengl/opengl_buffer.h"

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
            // context
            s_Data.api.createContext = gl_CreateContext;
            s_Data.api.clear = gl_Clear;
            s_Data.api.destroyContext = gl_DestroyContext;
            s_Data.api.makeActive = gl_MakeActive;
            s_Data.api.swapBuffers = gl_SwapBuffers;
            s_Data.api.setVsync = gl_SetVsync;
            s_Data.api.setClearColor = gl_SetClearColor;

            // buffer
            s_Data.api.createBuffer = gl_CreateBuffer;
            s_Data.api.destroyBuffer = gl_DestroyBuffer;
            s_Data.api.bindBuffer = gl_BindBuffer;
            s_Data.api.setBufferData = gl_SetBufferData;
            s_Data.api.submitArrays = _glSubmitArrays;
            s_Data.api.submitElements = _glSubmitElements;
            s_Data.api.submitLayout = _glSubmitLayout;

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
