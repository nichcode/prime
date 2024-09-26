#pragma once

#include "prime_defines.h"

namespace prime {

	/**
	 * @brief The template function for prime tests.
	 * Every test function should look like this function.
	 */
	using TestFunc = b8(*)();

	class TestManager
	{
	public:
	    
		/**
		 * @brief Add a new test to the test manager.
		 * 
		 * @param testFunc The function to run.
		 * @param name The name of the test.
		 */
		static void AddTest(TestFunc testFunc, const str& name);

		/**
		 * @brief Run all tests.
		 */
		static void Run();
	};
}
