
#include "prime/prime_test.h"

b8 WindowTest();
b8 MultiWindowTest();

int main(int argc, char** argv) 
{
	prime::TestManager::AddTest(WindowTest, "WindowTest");
	prime::TestManager::AddTest(MultiWindowTest, "MultiWindowTest");
	prime::TestManager::Run();

	return 0;
}