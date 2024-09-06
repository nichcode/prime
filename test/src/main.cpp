
#include "prime/prime_test.h"

b8 WindowTest();

int main(int argc, char** argv) 
{
	prime::TestManager::AddTest(WindowTest, "WindowTest");
	prime::TestManager::Run();

	return 0;
}