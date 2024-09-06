#pragma once

#include "prime_defines.h"

namespace prime {

	using TestFunc = b8(*)();

	class TestManager
	{
	public:
		static void Init();
		static void Shutdown();

		static void AddTest(TestFunc testFunc, const str& name);
		static void Run();
	};
}
