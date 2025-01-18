
#include "prime/prime.h"

b8
vec2Test()
{
	prLogInfo("");
	prLogInfo("Begin Vec2 Test");

	PrString* string = nullptr;
	PrVec2 x = prVec2Create(10.0f, 20.0f);
	PrVec2 y = prVec2Create(20.0f, 10.0f);
	PrVec2 result = x + y;

	result += prVec2Create(10.0f, 10.0f);
	result -= prVec2Create(10.0f, 10.0f);
	result /= prVec2Create(2.0f, 2.0f);
	result *= prVec2Create(2.0f, 2.0f);
	result *= 2.0f;

	string = prVec2ToString(result);
	prStringLog(string);
	prStringDestroy(string);

	prLogInfo("End Vec2 Test");
	prLogInfo("");
	return PR_PASSED;
}

b8
vec3Test()
{
	prLogInfo("");
	prLogInfo("Begin Vec3 Test");

	PrString* string = nullptr;
	PrVec3 x = prVec3Create(10.0f, 20.0f, 20.0f);
	PrVec3 y = prVec3Create(20.0f, 10.0f, 10.0f);
	PrVec3 result = x + y;

	result += prVec3Create(10.0f, 10.0f, 10.0f);
	result -= prVec3Create(10.0f, 10.0f, 10.0f);
	result /= prVec3Create(2.0f, 2.0f, 2.0f);
	result *= prVec3Create(2.0f, 2.0f, 2.0f);
	result *= 2.0f;

	string = prVec3ToString(result);
	prStringLog(string);
	prStringDestroy(string);

	prLogInfo("End Vec3 Test");
	prLogInfo("");
	return PR_PASSED;
}

b8
vec4Test()
{
	prLogInfo("");
	prLogInfo("Begin Vec4 Test");

	PrString* string = nullptr;
	PrVec4 x = prVec4Create(10.0f, 20.0f, 20.0f, 20.0f);
	PrVec4 y = prVec4Create(20.0f, 10.0f, 10.0f, 10.0f);
	PrVec4 result = x + y;

	result += prVec4Create(10.0f, 10.0f, 10.0f, 10.0f);
	result -= prVec4Create(10.0f, 10.0f, 10.0f, 10.0f);
	result /= prVec4Create(2.0f, 2.0f, 2.0f, 2.0f);
	result *= prVec4Create(2.0f, 2.0f, 2.0f, 2.0f);
	result *= 2.0f;

	string = prVec4ToString(result);
	prStringLog(string);
	prStringDestroy(string);

	prLogInfo("End Vec4 Test");
	prLogInfo("");
	return PR_PASSED;
}

b8
mat4Test()
{
	prLogInfo("");
	prLogInfo("Begin Mat4 Test");

	PrString* string_ortho = nullptr;
	PrString* string_perps = nullptr;
	PrString* string_translation = nullptr;
	PrString* string_rotation = nullptr;
	PrString* string_scale = nullptr;
	PrString* string_trs = nullptr;
	PrString* string_inverse = nullptr;

	PrMat4 ortho = prMat4Orthographic(0.0f, 640.0f, 480.0f, 0.0f, 1.0f, -1.0f);

	PrMat4 perps = prMat4Perspective(45.0f, 640.0f / 480.0f, 30.0f, 1000.0f);
	PrMat4 translation = prMat4Translation({2.0f, 11.0f, -2.0f});
	PrMat4 rotation = prMat4RotationZ(45.0f);
	PrMat4 scale = prMat4Scale({ 2.0f, 2.0f, 2.0f });
	PrMat4 trs = translation * rotation * scale;
	PrMat4 inverse = prMat4Inverse(trs);

	string_ortho = prMat4ToString(ortho);
	string_perps = prMat4ToString(perps);
	string_translation = prMat4ToString(translation);
	string_rotation = prMat4ToString(rotation);
	string_scale = prMat4ToString(scale);
	string_trs = prMat4ToString(trs);
	string_inverse = prMat4ToString(inverse);

	prStringLog(string_ortho);
	prStringLog(string_perps);
	prStringLog(string_translation);
	prStringLog(string_rotation);
	prStringLog(string_scale);
	prStringLog(string_trs);
	prStringLog(string_inverse);

	prStringDestroy(string_ortho);
	prStringDestroy(string_perps);
	prStringDestroy(string_translation);
	prStringDestroy(string_rotation);
	prStringDestroy(string_scale);
	prStringDestroy(string_trs);
	prStringDestroy(string_inverse);

	prLogInfo("End Mat4 Test");
	prLogInfo("");
	return PR_PASSED;
}