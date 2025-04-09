
#pragma once

#include "defines.h"

struct prWindow;

enum prWindowFlags_
{
    prWindowFlags_Show = PR_BIT(0),
    prWindowFlags_Center = PR_BIT(1)
};

PR_API prWindow* prCreateWindow(const char* title, u32 width, u32 height, u32 flags);
PR_API void prDestroyWindow(prWindow* window);
PR_API void prPullEvents();

PR_API b8 prWindowShouldClose(prWindow* window);