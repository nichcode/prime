#pragma once

#include "pr_defines.h"

using PrTestFunc = b8(*)();

struct PrTestEntry
{
	const char* name = nullptr;
	PrTestFunc function = nullptr;
};

PR_API void
prTestsAdd(PrTestFunc function, const char* name);

PR_API void
prTestsRun();
