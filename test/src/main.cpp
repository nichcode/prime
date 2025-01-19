
#include "tests.h"

int
main()
{
	prime_Init();

	// string
	prime_AddTest(stringTest, "StringTest");

	// window
	prime_AddTest(windowTest, "WindowTest");
	prime_AddTest(multiWindowTest, "MultiWindowTest");

	// context
	prime_AddTest(contextTestGL, "ContextTestGL");
	prime_AddTest(contextTestDx11, "ContextTestDx11");
	prime_AddTest(multiContextTest, "MultiContextTest");

	// maths
	prime_AddTest(vec2Test, "Vec2Test");
	prime_AddTest(vec3Test, "Vec3Test");
	prime_AddTest(vec4Test, "Vec4Test");
	prime_AddTest(mat4Test, "Mat4Test");

	// buffers
	prime_AddTest(staticBufferTestGL, "staticBufferTestGL");
	prime_AddTest(dynamicBufferTestGL, "dynamicBufferTestGL");

	prime_RunTests();
	prime_Shutdown();
	return 0;
}