
#include "windows_API.h"
#include "prime/core/platform.h"
#include "prime/core/logger.h"
#include "prime_utils.h"
#include "wgl_context.h"

namespace prime::core {

    i32 Platform::init()
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
        wc.lpfnWndProc = win32Proc;
        wc.lpszClassName = s_ClassName;
        wc.lpszMenuName = NULL;
        wc.style = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;

        ATOM success = RegisterClassExW(&wc);
        PRIME_ASSERT_MSG(success, "Window Registration Failed");

        utils::mapActionNames();
        utils::mapButtonNames();
        utils::mapKeyNames();

        internal::wglContextCreateDummy();

        PRIME_INFO("Win32Platform Init!");
        return 1;
    }

    void Platform::shutdown()
    {
        UnregisterClassW(s_ClassName, s_Instance);
        PRIME_INFO("Win32Platform Shutdown!");
    }  

} // namespace prime::core