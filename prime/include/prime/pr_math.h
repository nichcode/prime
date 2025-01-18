#pragma once

#include "pr_defines.h"

#define PR_PI 3.14159265358979323846f
#define PR_2PI (2.0f * PR_PI)
#define PR_SQRT_TWO 1.41421356237309504880f
#define PR_DEGTORAD_MULTIPLIER (PR_PI / 180.0f)
#define PR_RADTODEG_MULTIPLIER (180.0f / PR_PI)
#define PR_INFINITY (1e30f * 1e30f)
#define PR_FLOAT_EPSILON 1.192092896e-07f
#define PR_FLOAT_MIN -3.40282e+38F
#define PR_FLOAT_MAX 3.40282e+38F

PR_API f32
prMathSqrt(f32 number);

PR_API f32
prMathTan(f32 x);

PR_API f32
prMathCos(f32 x);

PR_API f32
prMathSin(f32 x);

PR_INLINE f32 
prMathRadiansToDegree(f32 radians) 
{
	return radians * PR_RADTODEG_MULTIPLIER;
}

PR_INLINE f32
prMathDegreeToRadians(f32 degrees)
{
	return degrees * PR_DEGTORAD_MULTIPLIER;
}