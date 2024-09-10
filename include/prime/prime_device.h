#pragma once

#include "prime_defines.h"
#include "prime_vertexbuffer.h"
#include "prime_ref.h"
#include "prime_devicetype.h"
#include "prime_indexbuffer.h"
#include "prime_viewport.h"

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
		IndexbufferHandle m_ActiveIndexbuffer;
		Viewport m_Viewport;

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
		void* GetNative() const;
		void* GetNativeContext() const;

		// create resources
		Ref<Vertexbuffer> CreateVertexBuffer(const void* data, u32 size, VertexbufferType type);
		Ref<Indexbuffer> CreateIndexBuffer(u32* indices, u32 count);

		void SetActiveVertexbuffer(VertexbufferHandle* vertexbufferHandle);
		void SetActiveIndexbuffer(IndexbufferHandle* indexbufferHandle);

		void SetViewport(const Viewport& viewport);

		// draw calls
		void DrawIndexed(PrimitiveTopology topology, u32 indexCount);

        PINLINE b8 IsActiveVertexbuffer(VertexbufferHandle& vertexbufferHandle) const
		{
			return m_ActiveVertexbuffer.Ptr == vertexbufferHandle.Ptr;
		}

		PINLINE b8 IsActiveIndexbuffer(IndexbufferHandle& indexbufferHandle) const
		{
			return m_ActiveIndexbuffer.Ptr == indexbufferHandle.Ptr;
		}
	};
}
