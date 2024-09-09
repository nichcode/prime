#pragma once

#include "prime_defines.h"
#include "prime_vertexbuffer.h"
#include "prime_ref.h"
#include "prime_devicetype.h"

namespace prime {

	class IDevice;
	class Window;

	class Device
	{
	private:
		IDevice* m_Driver;
		DeviceType m_Type;
		Window* m_Window;

		VertexbufferHandle m_ActiveVertexbuffer;

	public:
		Device() : m_Driver(nullptr), m_Type(DeviceTypeNone),
			m_Window(nullptr) {}
		Device(const Device&) = delete;
		Device& operator=(const Device&) = delete;

		void Init(DeviceType type, const Window* window);
		void Shutdown();

		void SetClearColor(f32 r, f32 g, f32 b, f32 a);
		void Clear();
		void SwapBuffers();

		PINLINE DeviceType GetType() const { return m_Type; }

		// create resources
		Ref<Vertexbuffer> CreateVertexBuffer(f32* vertices, u32 size, VertexbufferType type);
		Ref<Vertexbuffer> CreateVertexBuffer(u32 size, VertexbufferType type);

		void SetActiveVertexbuffer(VertexbufferHandle* vertexbufferHandle);

        PINLINE b8 IsActiveVertexbuffer(VertexbufferHandle& vertexbufferHandle) const
		{
			return m_ActiveVertexbuffer.Ptr == vertexbufferHandle.Ptr;
		}
	};
}
