
#include "prime/prime.h"

b8
mathTest()
{
    // vec2
	prime::vec2 vec2_x(10.0f, 20.0f);
	prime::vec2 vec2_y(20.0f, 10.0f);
	prime::vec2 vec2_result = vec2_x + vec2_y;

	vec2_result += { 10.0f, 10.0f };
	vec2_result -= { 10.0f, 10.0f };
	vec2_result /= { 2.0f, 2.0f };
	vec2_result *= { 2.0f, 2.0f };
	vec2_result *= 2.0f;

	str vec2_string = prime::vec2::toString(vec2_result);
    prime::Logger::info(vec2_string.c_str());

    return PTRUE;
}