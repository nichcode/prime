
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
	prInit();

	//prTestsAdd(stringTest, "StringTest");
	//prTestsAdd(windowTest, "WindowTest");
	//prTestsAdd(multiWindowTest, "MultiWindowTest");
	//prTestsAdd(contextTestGL, "ContextTestGL");
	//prTestsAdd(contextTestDx11, "ContextTestDx11");
	//prTestsAdd(multiContextTest, "MultiContextTest");
	//prTestsAdd(vec2Test, "Vec2Test");
	//prTestsAdd(vec3Test, "Vec3Test");
	//prTestsAdd(vec4Test, "Vec4Test");
	prTestsAdd(mat4Test, "Mat4Test");

	prTestsRun();
	prShutdown();
	return 0;
}