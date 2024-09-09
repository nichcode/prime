
#include "prime/prime_engine.h"
#include "platform/windows/wgl_context.h"

namespace prime {

	void Engine::Init()
	{
#ifdef PPLATFORM_WINDOWS
		DummyWglContext();
#endif // PPLATFORM_WINDOWS
	}
}