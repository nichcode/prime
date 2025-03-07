
#include "prime/prime.h"

b8 vec2Test()
{
    using namespace prime::maths;

    vec2 x(10.0f, 20.0f);
	vec2 y(20.0f, 10.0f);
	vec2 result = x + y;

	result += { 10.0f, 10.0f };
	result -= { 10.0f, 10.0f };
	result /= { 2.0f, 2.0f };
	result *= { 2.0f, 2.0f };
	result *= 2.0f;

	str string = vec2::toString(result);
    prime::core::Logger::info(string);

    return PRIME_TRUE;
}