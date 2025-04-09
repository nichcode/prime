
#pragma once

#include "prime/defines.h"

struct prWindow;
struct prContext;

struct State
{
    prContext* activeContext;
};

static State s_State;

void _InitInput();
void _ConsoleWrite(u32 level, const char* message);
b8 _WindowHasContext(prWindow* window);
void _SetWindowContext(prWindow* window, prContext* context);