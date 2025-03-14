
#pragma once

#include "prime/defines.h"
#include "entt/entt.hpp"

namespace prime::utils {

    i32 multibyteToWchar(const char* str, u32 str_len, wchar_t* wstr);
    i32 wcharToMultibyte(const wchar_t* wstr, u32 wstr_len, char* str);

    void consoleWrite(LogLevel level, const char* msg);

    void mapActionNames();
    void mapButtonNames();
    void mapKeyNames();

} // namespace prime::utils

namespace prime::scene {

    struct SceneHandle
    {
        entt::registry registry;
    };
    
} // namespace prime::scene
    