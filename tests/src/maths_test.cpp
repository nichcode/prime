
#include "prime/prime.h"

b8 mathsTest()
{
    using namespace prime::maths;

    // vec2
    vec2 vec2_x(10.0f, 20.0f);
	vec2 vec2_y(20.0f, 10.0f);
	vec2 vec2_result = vec2_x + vec2_y;

	vec2_result += { 10.0f, 10.0f };
	vec2_result -= { 10.0f, 10.0f };
	vec2_result /= { 2.0f, 2.0f };
	vec2_result *= { 2.0f, 2.0f };
	vec2_result *= 2.0f;
    prime::core::Logger::info(vec2::toString(vec2_result));

    // vec3
    vec3 vec3_x(10.0f, 20.0f, 20.0f);
	vec3 vec3_y(20.0f, 10.0f, 10.0f);
	vec3 vec3_result = vec3_x + vec3_y;

	vec3_result += { 10.0f, 10.0f, 10.0f };
	vec3_result -= { 10.0f, 10.0f, 10.0f };
	vec3_result /= { 2.0f, 2.0f, 2.0f };
	vec3_result *= { 2.0f, 2.0f, 2.0f };
	vec3_result *= 2.0f;
    prime::core::Logger::info(vec3::toString(vec3_result));

    // vec4
    vec4 vec4_x(10.0f, 20.0f, 20.0f, 20.0f);
	vec4 vec4_y(20.0f, 10.0f, 10.0f, 10.0f);
	vec4 vec4_result = vec4_x + vec4_y;

	vec4_result += { 10.0f, 10.0f, 10.0f, 10.0f };
	vec4_result -= { 10.0f, 10.0f, 10.0f, 10.0f };
	vec4_result /= { 2.0f, 2.0f, 2.0f, 2.0f };
	vec4_result *= { 2.0f, 2.0f, 2.0f, 2.0f };
	vec4_result *= 2.0f;
    prime::core::Logger::info(vec4::toString(vec4_result));

    // mat4
    mat4 ortho = mat4::orthographic(0.0f, 640.0f, 480.0f, 0.0f, 1.0f, -1.0f);

	mat4 perps = mat4::perspective(45.0f, 640.0f / 480.0f, 30.0f, 1000.0f);
	mat4 translation = mat4::translate({2.0f, 11.0f, -2.0f});
	mat4 rotation = mat4::rotateZ(45.0f);
	mat4 scale = mat4::scale({ 2.0f, 2.0f, 2.0f });
	mat4 trs = translation * rotation * scale;
	mat4 inverse = mat4::inverse(trs);

	prime::core::Logger::info(mat4::toString(ortho));
	prime::core::Logger::info(mat4::toString(perps));
	prime::core::Logger::info(mat4::toString(translation));
	prime::core::Logger::info(mat4::toString(rotation));
	prime::core::Logger::info(mat4::toString(scale));
	prime::core::Logger::info(mat4::toString(trs));
	prime::core::Logger::info(mat4::toString(inverse));

    return PRIME_TRUE;
}