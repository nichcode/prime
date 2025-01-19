
#include "prime/prime.h"

b8 
stringTest();

b8
windowTest();

b8
multiWindowTest();

b8
contextTestGL();

b8
contextTestDx11();

b8
multiContextTest();

b8
vec2Test();

b8
vec3Test();

b8
vec4Test();

b8
mat4Test();

int
main()
{
	prime_Init();

	prime_AddTest(stringTest, "StringTest");
	prime_AddTest(windowTest, "WindowTest");
	prime_AddTest(multiWindowTest, "MultiWindowTest");
	prime_AddTest(contextTestGL, "ContextTestGL");
	prime_AddTest(contextTestDx11, "ContextTestDx11");
	prime_AddTest(multiContextTest, "MultiContextTest");
	prime_AddTest(vec2Test, "Vec2Test");
	prime_AddTest(vec3Test, "Vec3Test");
	prime_AddTest(vec4Test, "Vec4Test");
	prime_AddTest(mat4Test, "Mat4Test");

	prime_RunTests();
	prime_Shutdown();
	return 0;
}