#pragma once

#include "prime/device.h"

namespace prime {

	class OpenGLDevice : public Device
	{
	public:
		OpenGLDevice();

		virtual DeviceTypes get_type() const override { return DeviceTypesOpenGL; }
		
		virtual Ref<Context> create_context(Window* window) override;

		virtual Ref<Vertexbuffer> create_vertexbuffer(const void* data, u32 size, VertexbufferType type) override;

		virtual Ref<Indexbuffer> create_indexbuffer(u32* indices, u32 count) override;

		virtual Ref<Shader> create_shader(const str& v_source, const str& p_source, b8 load) override;

		virtual Ref<Uniformbuffer> create_uniformbuffer(u32 size, u32 binding) override;

		virtual Ref<Texture2D> create_texture2d(const TextureProperties& props) override;
		virtual Ref<Texture2D> create_texture2d(const str& filepath) override;

		virtual Ref<RenderTarget> create_render_target(u32 width, u32 height, const Viewport* viewport) override;
	};
}
