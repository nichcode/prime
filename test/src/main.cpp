
#include "tests.h"

int
main()
{
	prime_Init();

	//// string
	//prime_TestManagerAddTest(stringTest, "StringTest");

	//// window
	//prime_TestManagerAddTest(windowTest, "WindowTest");
	//prime_TestManagerAddTest(multiWindowTest, "MultiWindowTest");

	//// context
	//prime_TestManagerAddTest(contextTestGL, "ContextTestGL");
	//prime_TestManagerAddTest(contextTestDx11, "ContextTestDx11");
	//prime_TestManagerAddTest(multiContextTest, "MultiContextTest");

	//// maths
	//prime_TestManagerAddTest(vec2Test, "Vec2Test");
	//prime_TestManagerAddTest(vec3Test, "Vec3Test");
	//prime_TestManagerAddTest(vec4Test, "Vec4Test");
	//prime_TestManagerAddTest(mat4Test, "Mat4Test");

	//// buffers
	//prime_TestManagerAddTest(staticBufferTestGL, "staticBufferTestGL");
	//prime_TestManagerAddTest(dynamicBufferTestGL, "dynamicBufferTestGL");

	//prime_TestManagerAddTest(shaderTestGL, "shaderTestGL");

	prime_TestManagerAddTest(renderer2DTestGL, "renderer2DTestGL");
	//prime_TestManagerAddTest(texture2DTestGL, "texture2DTestGL");

	prime_TestManagerRunTests();
	prime_Shutdown();
	return 0;
}