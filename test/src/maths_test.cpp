
#include "prime/prime.h"

b8
vec2Test()
{
	prLogInfo("");
	prLogInfo("Begin Vec2 Test");

	PrString* vec2_string = nullptr;
	PrVec2 vec2_x = prVec2Create(10.0f, 20.0f);
	PrVec2 vec2_y = prVec2Create(20.0f, 10.0f);
	PrVec2 vec2_result = prVec2Add(vec2_x, vec2_y);

	vec2_result = prVec2Add(vec2_result, { 10.0f, 10.0f });
	vec2_result = prVec2Sub(vec2_result, { 10.0f, 10.0f });
	vec2_result = prVec2Div(vec2_result, { 2.0f, 2.0f });
	vec2_result = prVec2Mul(vec2_result, { 2.0f, 2.0f });
	vec2_result = prVec2Scale(vec2_result, 2.0f);

	vec2_string = prVec2ToString(vec2_result);
	prStringLog(vec2_string);
	prStringDestroy(vec2_string);

	prLogInfo("End Vec2 Test");
	prLogInfo("");
	return PR_PASSED;
}

b8
vec3Test()
{
	prLogInfo("");
	prLogInfo("Begin Vec3 Test");

	PrString* vec3_string = nullptr;
	PrVec3 vec3_x = prVec3Create(10.0f, 20.0f, 20.0f);
	PrVec3 vec3_y = prVec3Create(20.0f, 10.0f, 10.0f);
	PrVec3 vec3_result = prVec3Add(vec3_x, vec3_y);

	vec3_result = prVec3Add(vec3_result, prVec3Create(10.0f, 10.0f, 10.0f));
	vec3_result = prVec3Sub(vec3_result, prVec3Create(10.0f, 10.0f, 10.0f));
	vec3_result = prVec3Div(vec3_result, prVec3Create(2.0f, 2.0f, 2.0f));
	vec3_result = prVec3Mul(vec3_result, prVec3Create(2.0f, 2.0f, 2.0f));
	vec3_result = prVec3Scale(vec3_result, 2.0f);

	vec3_string = prVec3ToString(vec3_result);
	prStringLog(vec3_string);
	prStringDestroy(vec3_string);

	prLogInfo("End Vec3 Test");
	prLogInfo("");
	return PR_PASSED;
}

b8
vec4Test()
{
	prLogInfo("");
	prLogInfo("Begin Vec4 Test");

	PrString* vec4_string = nullptr;
	PrVec4 vec4_x = prVec4Create(10.0f, 20.0f, 20.0f, 20.0f);
	PrVec4 vec4_y = prVec4Create(20.0f, 10.0f, 10.0f, 10.0f);
	PrVec4 vec4_result = prVec4Add(vec4_x, vec4_y);

	vec4_result = prVec4Add(vec4_result, prVec4Create(10.0f, 10.0f, 10.0f, 10.0f));
	vec4_result = prVec4Sub(vec4_result, prVec4Create(10.0f, 10.0f, 10.0f, 10.0f));
	vec4_result = prVec4Div(vec4_result, prVec4Create(2.0f, 2.0f, 2.0f, 2.0f));
	vec4_result = prVec4Mul(vec4_result, prVec4Create(2.0f, 2.0f, 2.0f, 2.0f));
	vec4_result = prVec4Scale(vec4_result, 2.0f);

	vec4_string = prVec4ToString(vec4_result);
	prStringLog(vec4_string);
	prStringDestroy(vec4_string);

	prLogInfo("End Vec4 Test");
	prLogInfo("");
	return PR_PASSED;
}