
#include "tests.h"

b8
vec2Test()
{
	prime_LogInfo("");
	prime_LogInfo("Begin Vec2 Test");

	prime_String* string = nullptr;
	prime_Vec2 x = prime_Vec2Create(10.0f, 20.0f);
	prime_Vec2 y = prime_Vec2Create(20.0f, 10.0f);
	prime_Vec2 result = x + y;

	result += prime_Vec2Create(10.0f, 10.0f);
	result -= prime_Vec2Create(10.0f, 10.0f);
	result /= prime_Vec2Create(2.0f, 2.0f);
	result *= prime_Vec2Create(2.0f, 2.0f);
	result *= 2.0f;

	string = prime_Vec2ToString(result);
	prime_LogString(string);
	prime_StringDestroy(string);

	prime_LogInfo("End Vec2 Test");
	prime_LogInfo("");
	return PRIME_PASSED;
}

b8
vec3Test()
{
	prime_LogInfo("");
	prime_LogInfo("Begin Vec3 Test");

	prime_String* string = nullptr;
	prime_Vec3 x = prime_Vec3Create(10.0f, 20.0f, 20.0f);
	prime_Vec3 y = prime_Vec3Create(20.0f, 10.0f, 10.0f);
	prime_Vec3 result = x + y;

	result += prime_Vec3Create(10.0f, 10.0f, 10.0f);
	result -= prime_Vec3Create(10.0f, 10.0f, 10.0f);
	result /= prime_Vec3Create(2.0f, 2.0f, 2.0f);
	result *= prime_Vec3Create(2.0f, 2.0f, 2.0f);
	result *= 2.0f;

	string = prime_Vec3ToString(result);
	prime_LogString(string);
	prime_StringDestroy(string);

	prime_LogInfo("End Vec3 Test");
	prime_LogInfo("");
	return PRIME_PASSED;
}

b8
vec4Test()
{
	prime_LogInfo("");
	prime_LogInfo("Begin Vec4 Test");

	prime_String* string = nullptr;
	prime_Vec4 x = prime_Vec4Create(10.0f, 20.0f, 20.0f, 20.0f);
	prime_Vec4 y = prime_Vec4Create(20.0f, 10.0f, 10.0f, 10.0f);
	prime_Vec4 result = x + y;

	result += prime_Vec4Create(10.0f, 10.0f, 10.0f, 10.0f);
	result -= prime_Vec4Create(10.0f, 10.0f, 10.0f, 10.0f);
	result /= prime_Vec4Create(2.0f, 2.0f, 2.0f, 2.0f);
	result *= prime_Vec4Create(2.0f, 2.0f, 2.0f, 2.0f);
	result *= 2.0f;

	string = prime_Vec4ToString(result);
	prime_LogString(string);
	prime_StringDestroy(string);

	prime_LogInfo("End Vec4 Test");
	prime_LogInfo("");
	return PRIME_PASSED;
}

b8
mat4Test()
{
	prime_LogInfo("");
	prime_LogInfo("Begin Mat4 Test");

	prime_String* string_ortho = nullptr;
	prime_String* string_perps = nullptr;
	prime_String* string_translation = nullptr;
	prime_String* string_rotation = nullptr;
	prime_String* string_scale = nullptr;
	prime_String* string_trs = nullptr;
	prime_String* string_inverse = nullptr;

	prime_Mat4 ortho = prime_Mat4Orthographic(0.0f, 640.0f, 480.0f, 0.0f, 1.0f, -1.0f);

	prime_Mat4 perps = prime_Mat4Perspective(45.0f, 640.0f / 480.0f, 30.0f, 1000.0f);
	prime_Mat4 translation = prime_Mat4Translation({2.0f, 11.0f, -2.0f});
	prime_Mat4 rotation = prime_Mat4RotationZ(45.0f);
	prime_Mat4 scale = prime_Mat4Scale({ 2.0f, 2.0f, 2.0f });
	prime_Mat4 trs = translation * rotation * scale;
	prime_Mat4 inverse = prime_Mat4Inverse(trs);

	string_ortho = prime_Mat4ToString(ortho);
	string_perps = prime_Mat4ToString(perps);
	string_translation = prime_Mat4ToString(translation);
	string_rotation = prime_Mat4ToString(rotation);
	string_scale = prime_Mat4ToString(scale);
	string_trs = prime_Mat4ToString(trs);
	string_inverse = prime_Mat4ToString(inverse);

	prime_LogString(string_ortho);
	prime_LogString(string_perps);
	prime_LogString(string_translation);
	prime_LogString(string_rotation);
	prime_LogString(string_scale);
	prime_LogString(string_trs);
	prime_LogString(string_inverse);

	prime_StringDestroy(string_ortho);
	prime_StringDestroy(string_perps);
	prime_StringDestroy(string_translation);
	prime_StringDestroy(string_rotation);
	prime_StringDestroy(string_scale);
	prime_StringDestroy(string_trs);
	prime_StringDestroy(string_inverse);

	prime_LogInfo("End Mat4 Test");
	prime_LogInfo("");
	return PRIME_PASSED;
}