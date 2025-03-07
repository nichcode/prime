
#include "prime/core/platform.h"
#include "prime/core/logger.h"

namespace prime::core {

    i32 Platform::init()
    {
        PRIME_INFO("Win32Platform Init!");
        return 1;
    }

    void Platform::shutdown()
    {
        PRIME_INFO("Win32Platform Shutdown!");
    }   
    

} // namespace prime::core