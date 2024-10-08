
#include "prime/prime_test.h"
#include "prime/prime_engine.h"

b8 WindowTest();
b8 DeviceTest();

int main(int argc, char** argv) 
{
	prime::Engine::Init();

	//prime::TestManager::AddTest(WindowTest, "WindowTest");
	prime::TestManager::AddTest(DeviceTest, "DeviceTest");
	prime::TestManager::Run();

	return 0;
}