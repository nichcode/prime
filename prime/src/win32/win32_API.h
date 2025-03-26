
#pragma once

#include "pch.h"

#include "ft2build.h"
#include FT_FREETYPE_H

static HINSTANCE s_Instance;

static const wchar_t* s_ClassName = L"WindowClass";
static const wchar_t* s_PropName = L"WindowData";

static FT_Library s_Library;

LRESULT CALLBACK win32Proc(HWND hwnd, u32 msg, WPARAM w_param, LPARAM l_param);