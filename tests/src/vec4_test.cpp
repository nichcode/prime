
#include "prime/prime.h"

b8 vec4Test()
{
    using namespace prime::maths;

    vec4 x(10.0f, 20.0f, 20.0f, 20.0f);
	vec4 y(20.0f, 10.0f, 10.0f, 10.0f);
	vec4 result = x + y;

	result += { 10.0f, 10.0f, 10.0f, 10.0f };
	result -= { 10.0f, 10.0f, 10.0f, 10.0f };
	result /= { 2.0f, 2.0f, 2.0f, 2.0f };
	result *= { 2.0f, 2.0f, 2.0f, 2.0f };
	result *= 2.0f;

	str string = vec4::toString(result);
    prime::core::Logger::info(string);

    return PRIME_TRUE;
}