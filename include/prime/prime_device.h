#pragma once

#include "prime_defines.h"
#include "prime_vertexbuffer.h"
#include "prime_ref.h"
#include "prime_devicetype.h"
#include "prime_indexbuffer.h"
#include "prime_viewport.h"
#include "prime_shader.h"
#include "prime_uniformbuffer.h"
#include "prime_texture.h"
#include "prime_render_target.h"

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
		ShaderHandle m_ActiveShaderHandle;
		UniformbufferHandle m_ActiveUniformbuffer;
		Texture2DHandle m_ActiveTexture2DHandle;
		RenderTargetHandle m_ActiveRenderTargetHandle;
		Viewport m_Viewport;

		// TODO: save refs of textures and resources to not recreate them again

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
		Ref<Shader> CreateShader(const str& VSource, const str& PSource, b8 load);
		Ref<Uniformbuffer> CreateUniformbuffer(u32 size, u32 binding);
		Ref<Texture2D> CreateTexture2D(const TextureProperties& props);
		Ref<Texture2D> CreateTexture2D(const str& filepath);
		Ref<RenderTarget> CreateRenderTarget(u32 width, u32 height, const Viewport* viewport);

		void SetActiveVertexbuffer(VertexbufferHandle* vertexbufferHandle);
		void SetActiveIndexbuffer(IndexbufferHandle* indexbufferHandle);
		void SetActiveShader(ShaderHandle* shaderHandle);
		void SetActiveUniformbuffer(UniformbufferHandle* uniformbufferHandle);
		void SetActiveTexture2DHandle(Texture2DHandle* textureHandle);
		void SetActiveRenderTargetHandle(RenderTargetHandle* renderTargetHandle);

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

		PINLINE b8 IsActiveShader(ShaderHandle& shaderHandle) const
		{
			return m_ActiveShaderHandle.Ptr == shaderHandle.Ptr;
		}

		PINLINE b8 IsActiveUniformbuffer(UniformbufferHandle& uniformbufferHandle) const
		{
			return m_ActiveUniformbuffer.Ptr == uniformbufferHandle.Ptr;
		}

		PINLINE b8 IsActiveTextureHandle(Texture2DHandle& textureHandle) const
		{
			return m_ActiveTexture2DHandle.Ptr == textureHandle.Ptr;
		}

		PINLINE b8 IsActiveRenderTargetHandle(RenderTargetHandle& renderTargetHandle) const
		{
			return m_ActiveRenderTargetHandle.Ptr == renderTargetHandle.Ptr;
		}
	};
}
