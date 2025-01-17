#pragma once

#include "prime/pr_defines.h"
#include "prime/pr_memory.h"
#include "prime/pr_color.h"

#include <vector>

#ifdef PR_PLATFORM_WINDOWS
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // !WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include "windows/pr_win32platform.h"
#endif // PR_PLATFORM_WINDOWS

struct PrContext;
struct PrWindow;
struct PrDevice;

struct PrDevice
{
	std::vector<PrContext*> contexts;
	PrContext* activeContext = nullptr;
	PrDriverType type;
};

struct PrContext
{
	PrDevice* device = nullptr;
	PrWindow* window = nullptr;
	b8 vSync = false;
	PrColor color;

#ifdef PR_PLATFORM_WINDOWS
	HGLRC handle = nullptr;
#endif // PR_PLATFORM_WINDOWS
};

struct PrWindow
{
#ifdef PR_PLATFORM_WINDOWS
	HWND handle = nullptr;
	HGLRC context = nullptr;
#endif // PR_PLATFORM_WINDOWS

	u32 width = 0;
	u32 height = 0;
	PrString* title = nullptr;
	b8 shouldClose = false, isFocused = false;
	b8 isHidden = false;

	u16 keycodes[512] = {};
	u16 scancodes[PrKey_Max + 1] = {};

	u8 keys[PrKey_Max + 1] = {};
	u8 buttons[PrButton_Max + 1] = {};

	i32 mousePos[2] = {};
	u32 minWidth = 0, maxWidth = 0;
	u32 minHeight = 0, maxHeight = 0;

	void* userData = nullptr;
	i32 posX = 0;
	i32 posY = 0;
};

struct PrString
{
	u64 length = 0;
	char* buffer = nullptr;
};

struct PrWideString
{
	u64 length = 0;
	wchar_t* buffer = nullptr;
};
