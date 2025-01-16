
#include "prime/prime.h"

#ifdef PR_PLATFORM_WINDOWS

PR_API b8
prInit()
{
	return PR_PASSED;
}

PR_API void
prShutdown()
{

}

#endif // PR_PLATFORM_WINDOWS
