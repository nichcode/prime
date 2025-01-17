#pragma once

#include "pr_defines.h"

using PrimeTestFunc = b8(*)();

struct PrTestEntry
{
	const char* name = nullptr;
	PrimeTestFunc function = nullptr;
};

PR_API void
prTestsAdd(const PrTestEntry& test_entry);

PR_API void
prTestsRun();
