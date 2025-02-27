
#include "prime/platform.h"
#include "prime/logger.h"
#include "prime/utils.h"
#include "wgl_context.h"

#include "opengl/opengl_device.h"

#include <memory.h>

#ifdef PPLATFORM_WINDOWS
#include "windows_API.h"

static u64 s_UsedMemory = 0;

namespace prime {

    b8 
    Platform::init()
    {
        s_Instance = GetModuleHandleW(nullptr);

        WNDCLASSEXW wc = {};
        wc.cbClsExtra = 0;
        wc.cbSize = sizeof(WNDCLASSEXW);
        wc.cbWndExtra = 0;
        wc.hbrBackground = NULL;
        wc.hCursor = LoadCursor(s_Instance, IDC_ARROW);
        wc.hIcon = LoadIcon(s_Instance, IDI_APPLICATION);
        wc.hIconSm = LoadIcon(s_Instance, IDI_APPLICATION);
        wc.hInstance = s_Instance;
        wc.lpfnWndProc = primeWin32Proc;
        wc.lpszClassName = s_ClassName;
        wc.lpszMenuName = NULL;
        wc.style = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;

        ATOM success = RegisterClassExW(&wc);
        PASSERT_MSG(success, "Window Registration Failed");
    
        Utils::init();
        wglContextCreateDummy();

        PINFO("Prime Windows Platform Init");
        return true;
    }

    void 
    Platform::shutdown()
    {
        UnregisterClassW(s_ClassName, s_Instance);
        PINFO("Prime Windows Platform Shutdown");
    }

    Ref<Device> Platform::createDevice(DeviceType type, const Window& window)
    {
        switch (type)
        {
            case DeviceType::OpenGL: {
                return createRef<GLDevice>(window);
            }
            break;
        }
        return nullptr;
    }
    

    void 
    Logger::setLevel(LogLevel level, b8 reset)
    {
        HANDLE console = NULL;
        static u8 levels[4] = { 8, 2, 6, 4 };
        b8 error = level > LogLevel::Warn;

        if (error) {
            console = GetStdHandle(STD_ERROR_HANDLE);
        }
        else {
            console = GetStdHandle(STD_OUTPUT_HANDLE);
        }

        if (reset) {
            SetConsoleTextAttribute(console, 15);
        }
        else {
            SetConsoleTextAttribute(console, levels[(u32)level]);
        }
    }

    i32
    multibyteToWchar(const char* str, u32 str_len, wchar_t* wstr)
    {
        return MultiByteToWideChar(CP_UTF8, 0, str, -1, wstr, str_len);
    }

    i32
    wcharToMultibyte(const wchar_t* wstr, u32 wstr_len, char* str)
    {
        return WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, wstr_len, 0, 0);
    }

} // namespace prime

#endif // PPLATFORM_WINDOWS