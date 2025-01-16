#pragma once

#include "pr_defines.h"

using PrimeTestFunc = b8(*)();

struct PrTestEntry
{
	const char* name = nullptr;
	PrimeTestFunc function = nullptr;
};

void
prTestsAdd(const PrTestEntry& test_entry);

void
prTestsRun();
