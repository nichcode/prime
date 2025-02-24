
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

    // vec4
	prime::vec4 vec4_x(10.0f, 20.0f, 20.0f, 20.0f);
	prime::vec4 vec4_y(20.0f, 10.0f, 10.0f, 10.0f);
	prime::vec4 vec4_result = vec4_x + vec4_y;

	vec4_result += { 10.0f, 10.0f, 10.0f, 10.0f };
	vec4_result -= { 10.0f, 10.0f, 10.0f, 10.0f };
	vec4_result /= { 2.0f, 2.0f, 2.0f, 2.0f };
	vec4_result *= { 2.0f, 2.0f, 2.0f, 2.0f };
	vec4_result *= 2.0f;

	str vec4_string = prime::vec4::toString(vec4_result);
    prime::Logger::info(vec4_string.c_str());

    // mat4
	prime::mat4 ortho = prime::mat4::orthographic(0.0f, 640.0f, 480.0f, 0.0f, 1.0f, -1.0f);

	prime::mat4 perps = prime::mat4::perspective(45.0f, 640.0f / 480.0f, 30.0f, 1000.0f);
	prime::mat4 translation = prime::mat4::translate({2.0f, 11.0f, -2.0f});
	prime::mat4 rotation = prime::mat4::rotateZ(45.0f);
	prime::mat4 scale = prime::mat4::scale({ 2.0f, 2.0f, 2.0f });
	prime::mat4 trs = translation * rotation * scale;
	prime::mat4 inverse = prime::mat4::inverse(trs);

	str string_ortho = prime::mat4::toString(ortho);
	str string_perps = prime::mat4::toString(perps);
	str string_translation = prime::mat4::toString(translation);
	str string_rotation = prime::mat4::toString(rotation);
	str string_scale = prime::mat4::toString(scale);
	str string_trs = prime::mat4::toString(trs);
	str string_inverse = prime::mat4::toString(inverse);

	prime::Logger::info(string_ortho.c_str());
	prime::Logger::info(string_perps.c_str());
	prime::Logger::info(string_translation.c_str());
	prime::Logger::info(string_rotation.c_str());
	prime::Logger::info(string_scale.c_str());
	prime::Logger::info(string_trs.c_str());
	prime::Logger::info(string_inverse.c_str());

    return PTRUE;
}