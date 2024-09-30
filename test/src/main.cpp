
#include "prime/prime_test.h"
#include "prime/prime_device.h"

b8 WindowTest();
b8 DeviceTest();
b8 GameTest();
b8 Vec2Test();
b8 Vec3Test();

int main(int argc, char** argv) 
{
	//prime::TestManager::AddTest(WindowTest, "WindowTest");
	//prime::TestManager::AddTest(DeviceTest, "DeviceTest");
	//prime::TestManager::AddTest(GameTest, "GameTest");
	//prime::TestManager::AddTest(Vec2Test, "Vec2Test");
	prime::TestManager::AddTest(Vec3Test, "Vec3Test");
	prime::TestManager::Run();

	return 0;
}