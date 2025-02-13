
#include "prime/prime_defines.h"

using prime_TestFunc = b8(*)();

PAPI u8
prime_AddTest(const char* name, prime_TestFunc func);

PAPI void 
prime_RunTests();