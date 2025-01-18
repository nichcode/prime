
#include "prime/prime.h"

b8
vec2Test()
{
	prLogInfo("");
	prLogInfo("Begin Vec2 Test");

	PrString* string = nullptr;
	PrVec2 x = prVec2Create(10.0f, 20.0f);
	PrVec2 y = prVec2Create(20.0f, 10.0f);
	PrVec2 result = prVec2Add(x, y);

	result = prVec2Add(result, { 10.0f, 10.0f });
	result = prVec2Sub(result, { 10.0f, 10.0f });
	result = prVec2Div(result, { 2.0f, 2.0f });
	result = prVec2Mul(result, { 2.0f, 2.0f });
	result = prVec2Scale(result, 2.0f);

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
	PrVec3 result = prVec3Add(x, y);

	result = prVec3Add(result, prVec3Create(10.0f, 10.0f, 10.0f));
	result = prVec3Sub(result, prVec3Create(10.0f, 10.0f, 10.0f));
	result = prVec3Div(result, prVec3Create(2.0f, 2.0f, 2.0f));
	result = prVec3Mul(result, prVec3Create(2.0f, 2.0f, 2.0f));
	result = prVec3Scale(result, 2.0f);

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
	PrVec4 result = prVec4Add(x, y);

	result = prVec4Add(result, prVec4Create(10.0f, 10.0f, 10.0f, 10.0f));
	result = prVec4Sub(result, prVec4Create(10.0f, 10.0f, 10.0f, 10.0f));
	result = prVec4Div(result, prVec4Create(2.0f, 2.0f, 2.0f, 2.0f));
	result = prVec4Mul(result, prVec4Create(2.0f, 2.0f, 2.0f, 2.0f));
	result = prVec4Scale(result, 2.0f);

	string = prVec4ToString(result);
	prStringLog(string);
	prStringDestroy(string);

	prLogInfo("End Vec4 Test");
	prLogInfo("");
	return PR_PASSED;
}

b8
quatTest()
{
	prLogInfo("");
	prLogInfo("Begin Quat Test");

	PrString* string = nullptr;
	PrQuat quat = prQuatCreate(1.0f, 2.0f, 10.0f, 20.0f);

	string = prQuatToString(quat);
	prStringLog(string);
	prStringDestroy(string);

	prLogInfo("End Quat Test");
	prLogInfo("");
	return PR_PASSED;
}

b8
mat4Test()
{
	prLogInfo("");
	prLogInfo("Begin Mat4 Test");

	PrString* string = nullptr;
	PrMat4 mat4 = prMat4Identity();

	string = prMat4ToString(mat4);
	prStringLog(string);
	prStringDestroy(string);

	prLogInfo("End Mat4 Test");
	prLogInfo("");
	return PR_PASSED;
}