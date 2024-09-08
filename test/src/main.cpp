
#include "prime/prime_test.h"

b8 WindowTest();
b8 MultiWindowTest();
b8 DirectX11DeviceTest();
b8 OpenGLDeviceTest();
b8 MultiDeviceTest();

int main(int argc, char** argv) 
{
	//prime::TestManager::AddTest(WindowTest, "WindowTest");
	//prime::TestManager::AddTest(MultiWindowTest, "MultiWindowTest");
	//prime::TestManager::AddTest(DirectX11DeviceTest, "DirectX11DeviceTest");
	//prime::TestManager::AddTest(OpenGLDeviceTest, "OpenGLDeviceTest");
	prime::TestManager::AddTest(MultiDeviceTest, "MultiDeviceTest");
	prime::TestManager::Run();

	return 0;
}