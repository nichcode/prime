
#include "prime/prime.h"

b8
mathTest()
{
    // vec2
    char* vec2_string = nullptr;
	primeVec2 vec2_x = primeVec2Create(10.0f, 20.0f);
	primeVec2 vec2_y = primeVec2Create(20.0f, 10.0f);
	primeVec2 vec2_result = vec2_x + vec2_y;

	vec2_result += primeVec2Create(10.0f, 10.0f);
	vec2_result -= primeVec2Create(10.0f, 10.0f);
	vec2_result /= primeVec2Create(2.0f, 2.0f);
	vec2_result *= primeVec2Create(2.0f, 2.0f);
	vec2_result *= 2.0f;

	vec2_string = primeVec2ToString(vec2_result);
    primeLogInfo(vec2_string);
    primeStringFree(vec2_string);

    // vec3
    char* vec3_string = nullptr;
	primeVec3 vec3_x = primeVec3Create(10.0f, 20.0f, 20.0f);
	primeVec3 vec3_y = primeVec3Create(20.0f, 10.0f, 10.0f);
	primeVec3 vec3_result = vec3_x + vec3_y;

	vec3_result += primeVec3Create(10.0f, 10.0f, 10.0f);
	vec3_result -= primeVec3Create(10.0f, 10.0f, 10.0f);
	vec3_result /= primeVec3Create(2.0f, 2.0f, 2.0f);
	vec3_result *= primeVec3Create(2.0f, 2.0f, 2.0f);
	vec3_result *= 2.0f;

	vec3_string = primeVec3ToString(vec3_result);
    primeLogInfo(vec3_string);
    primeStringFree(vec3_string);

    // vec4
    char* vec4_string = nullptr;
	primeVec4 vec4_x = primeVec4Create(10.0f, 20.0f, 20.0f, 20.0f);
	primeVec4 vec4_y = primeVec4Create(20.0f, 10.0f, 10.0f, 10.0f);
	primeVec4 vec4_result = vec4_x + vec4_y;

	vec4_result += primeVec4Create(10.0f, 10.0f, 10.0f, 10.0f);
	vec4_result -= primeVec4Create(10.0f, 10.0f, 10.0f, 10.0f);
	vec4_result /= primeVec4Create(2.0f, 2.0f, 2.0f, 2.0f);
	vec4_result *= primeVec4Create(2.0f, 2.0f, 2.0f, 2.0f);
	vec4_result *= 2.0f;

	vec4_string = primeVec4ToString(vec4_result);
    primeLogInfo(vec4_string);
    primeStringFree(vec4_string);

    // mat4
    char* string_ortho = nullptr;
	char* string_perps = nullptr;
	char* string_translation = nullptr;
	char* string_rotation = nullptr;
	char* string_scale = nullptr;
	char* string_trs = nullptr;
	char* string_inverse = nullptr;

	primeMat4 ortho = primeMat4Orthographic(0.0f, 640.0f, 480.0f, 0.0f, 1.0f, -1.0f);

	primeMat4 perps = primeMat4Perspective(45.0f, 640.0f / 480.0f, 30.0f, 1000.0f);
	primeMat4 translation = primeMat4Translation({2.0f, 11.0f, -2.0f});
	primeMat4 rotation = primeMat4RotationZ(45.0f);
	primeMat4 scale = primeMat4Scale({ 2.0f, 2.0f, 2.0f });
	primeMat4 trs = translation * rotation * scale;
	primeMat4 inverse = primeMat4Inverse(trs);

	string_ortho = primeMat4ToString(ortho);
	string_perps = primeMat4ToString(perps);
	string_translation = primeMat4ToString(translation);
	string_rotation = primeMat4ToString(rotation);
	string_scale = primeMat4ToString(scale);
	string_trs = primeMat4ToString(trs);
	string_inverse = primeMat4ToString(inverse);

	primeLogInfo(string_ortho);
	primeLogInfo(string_perps);
	primeLogInfo(string_translation);
	primeLogInfo(string_rotation);
	primeLogInfo(string_scale);
	primeLogInfo(string_trs);
	primeLogInfo(string_inverse);

	primeStringFree(string_ortho);
	primeStringFree(string_perps);
	primeStringFree(string_translation);
	primeStringFree(string_rotation);
	primeStringFree(string_scale);
	primeStringFree(string_trs);
	primeStringFree(string_inverse);

    return true;
}