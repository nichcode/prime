
#include "prime/prime.h"

b8 Vec3Test()
{
	prime::Vec3 rhs(10.45f);
	prime::Vec3 lhs(5.0f, 5.0f, 5.0f);
	prime::Vec3 result;

	PDEBUG(rhs);
	PDEBUG(lhs);
	PDEBUG(result);

	PDEBUG("Adding lhs with rhs to result");
	result = lhs + rhs;
	PDEBUG(result);

	PDEBUG("Subtracting rhs from lhs to result");
	result = lhs - rhs;
	PDEBUG(result);

	PDEBUG("Multiplying rhs with lhs to result");
	result = lhs * rhs;
	PDEBUG(result);

	PDEBUG("Deviding rhs with lhs to result");
	result = lhs / rhs;
	PDEBUG(result);

	PDEBUG("Setting result to zero");
	result.Zero();
	PDEBUG(result);

	PDEBUG("Adding rhs to result");
	result += rhs;
	PDEBUG(result);

	PDEBUG("Subtracting lhs from result");
	result -= lhs;
	PDEBUG(result);

	PDEBUG("Multiplying result with rhs");
	result *= rhs;
	PDEBUG(result);

	PDEBUG("Deviding result with rhs");
	result /= rhs;
	PDEBUG(result);

	PDEBUG("Multiplying rhs with a scaler of 2 to result");
	result = rhs * 2.0f;
	PDEBUG(result);

	PDEBUG("Multiplying result with a scaler of 2");
	result *= 2.0f;
	PDEBUG(result);

	PDEBUG("Deviding result with a scaler of 2");
	result /= 2.0f;
	PDEBUG(result);

	PDEBUG("Length squared of result");
	PDEBUG(result.LengthSquared());

	PDEBUG("Length of result");
	PDEBUG(result.Length());

	PDEBUG("Distance squared of result from rhs");
	PDEBUG(result.DistanceSquared(rhs));

	PDEBUG("Distance of result from rhs");
	PDEBUG(result.Distance(rhs));

	PDEBUG("Check to see if result is the same as rhs");
	PDEBUG(result == rhs);

	PDEBUG("Check to see if result is not the same as rhs");
	PDEBUG(result != rhs);

	PDEBUG("Setting result to one");
	PDEBUG("Setting rhs to one");
	result.One();
	rhs.One();

	PDEBUG("Check to see if result is the same as rhs");
	PDEBUG(result == rhs);

	return PPASSED;
}