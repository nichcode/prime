
#include "pch.h"
#include "prime_API.h"

#include "opengl/opengl_context.h"
#include "opengl/opengl_buffer.h"
#include "opengl/opengl_shader.h"

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
            s_Data.api.submitArrays = gl_SubmitArrays;
            s_Data.api.submitElements = gl_SubmitElements;
            s_Data.api.submitLayout = gl_SubmitLayout;

            // buffer
            s_Data.api.createBuffer = gl_CreateBuffer;
            s_Data.api.destroyBuffer = gl_DestroyBuffer;
            s_Data.api.bindBuffer = gl_BindBuffer;
            s_Data.api.setBufferData = gl_SetBufferData;

            // shader
            s_Data.api.createShader = gl_CreateShader;
            s_Data.api.destroyShader = gl_DestroyShader;
            s_Data.api.bindShader = gl_BindShader;
            s_Data.api.setInt = gl_SetInt;
            s_Data.api.setIntArray = gl_SetIntArray;
            s_Data.api.setFloat = gl_SetFloat;
            s_Data.api.setFloat2 = gl_SetFloat2;
            s_Data.api.setFloat3 = gl_SetFloat3;
            s_Data.api.setFloat4 = gl_SetFloat4;
            s_Data.api.setMat4 = gl_SetMat4;
            

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
