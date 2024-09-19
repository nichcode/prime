
#include "prime/prime_engine.h"
#include "platform/windows/wgl_context.h"
#include "prime/prime_time.h"

namespace prime {

	void Engine::Init()
	{
#ifdef PPLATFORM_WINDOWS
		DummyWglContext();
#endif // PPLATFORM_WINDOWS

		Time::Init();
	}
}