
#pragma once

#include "prime/defines.h"
#include "entt/entt.hpp"
#include <box2d/box2d.h>

#define PRIME_P2M 30.0f

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

namespace prime::core {

    PRIME_INLINE b2BodyType getBodyType(BodyType2D type)
	{
		switch (type) {
            case BodyType2DStatic:    return b2_staticBody; break;
            case BodyType2DDynamic:   return b2_dynamicBody; break;
            case BodyType2DKinematic: return b2_kinematicBody; break;
		}
		return b2_staticBody;
	}
    
} // namespace prime::core

    