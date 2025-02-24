
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

    // vec3
	prime::vec3 vec3_x(10.0f, 20.0f, 20.0f);
	prime::vec3 vec3_y(20.0f, 10.0f, 10.0f);
	prime::vec3 vec3_result = vec3_x + vec3_y;

	vec3_result += { 10.0f, 10.0f, 10.0f };
	vec3_result -= { 10.0f, 10.0f, 10.0f };
	vec3_result /= { 2.0f, 2.0f, 2.0f };
	vec3_result *= { 2.0f, 2.0f, 2.0f };
	vec3_result *= 2.0f;

	str vec3_string = prime::vec3::toString(vec3_result);
    prime::Logger::info(vec3_string.c_str());

    return PTRUE;
}