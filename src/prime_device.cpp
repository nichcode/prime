
#include "prime/prime_device.h"
#include "prime_idevice.h"
#include "prime/prime_window.h"

namespace prime {

	void Device::Init(DeviceType type, const Window* window)
	{
		if (!m_Driver) {
			m_Driver = IDevice::Create(type);
			m_Driver->Init(window);
			m_Type = type;
		}
	}

	void Device::Shutdown()
	{
		if (m_Driver) {
			m_Driver->Shutdown();
			delete m_Driver;
			m_Driver = nullptr;
			m_Type = DeviceTypeNone;
		}
	}

	void Device::SetClearColor(f32 r, f32 g, f32 b, f32 a)
	{
		m_Driver->SetClearColor(r, g, b, a);
	}

	void Device::Clear()
	{
		m_Driver->Clear();
	}

	void Device::SwapBuffers()
	{
		m_Driver->SwapBuffers();
	}
}