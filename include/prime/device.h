#pragma once

#include "context.h"
#include "ref.h"
#include "scope.h"
#include "indexbuffer.h"
#include "vertexbuffer.h"
#include "shader.h"
#include "uniformbuffer.h"
#include "texture2d.h"
#include "render_target.h"

namespace prime {

	class Window;

	enum DeviceTypes : u8
	{
		DeviceTypesNone,

#ifdef PPLATFORM_WINDOWS
		DeviceTypesDirectX11,
		DeviceTypesOpenGL
#endif // PPLATFORM_WINDOWS
	};

	class Device
	{
	public:
        /**
         * @brief Get the type of the device.
         * 
         * @return the device type.
         */
		virtual DeviceTypes get_type() const = 0;

		/**
		 * @brief Create a rendering context.
		 * @return The created rendering context otherwise nullptr.
		 */
		virtual Ref<Context> create_context(Window* window) = 0;

		/**
		 * @brief Create a vertexbuffer object.
		 * @param data The data for the vertexbuffer. This can be a nullptr.
		 * @param size The size of the vertexbuffer.
		 * @param type The type of the vertexbuffer ie. static or dynamic.
		 * @return The created vertexbuffer otherwise nullptr.
		 */
		virtual Ref<Vertexbuffer> create_vertexbuffer(const void* data, u32 size, VertexbufferType type) = 0;
        
		/**
		 * @brief Create a indexbuffer object. 
		 * Prime supports only 32bit indices.
		 * @param indices The indices which the index buffer will stored and use. 
		 * @param count The number of indices.
		 * @return The createdindexbuffer otherwise nullptr.
		 */
		virtual Ref<Indexbuffer> create_indexbuffer(u32* indices, u32 count) = 0;

		/**
		 * @brief Create a shader object.
		 * @param v_source The vertexshader source.
		 * @param p_source The pixelshader source.
		 * @param load If true the Vsource and PSource will be loaded as files from disk.
		 * @return The created shader otherwise nullptr.
		 */
		virtual Ref<Shader> create_shader(const str& v_source, const str& p_source, b8 load) = 0;

		/**
		 * @brief Create a uniformbuffer object.
		 * @param size The size of the uniformbuffer.
		 * @param binding The binding slot to use for the uniform buffer.
		 * @return The created uniformbuffer otherwise nullptr.
		 */
		virtual Ref<Uniformbuffer> create_uniformbuffer(u32 size, u32 binding) = 0;

		/**
		 * @brief Create a Texture2d object.
		 * @param props The properties of the texture2d.
		 * @return The created texture2d otherwise nullptr.
		 */
		virtual Ref<Texture2D> create_texture2d(const TextureProperties& props) = 0;

		/**
		 * @brief Load a Texture2d object.
		 * @param filepath The filepath to load the texture2d.
		 * @return The created texture2d otherwise nullptr.
		 */
		virtual Ref<Texture2D> create_texture2d(const str& filepath) = 0;

		/**
		 * @brief Create a rendertarget object.
		 * @param width The width of the rendertarget.
		 * @param height The height of the rendertarget.
		 * @param viewport A pointer to the viewport of the device.
		 * @return The created rendertarget otherwise nullptr.
		 */
		virtual Ref<RenderTarget> create_render_target(u32 width, u32 height, const Viewport* viewport) = 0;

		/**
		 * @brief Create a device;
		 * @param type The device type.
		 */
		static Scope<Device> create(DeviceTypes type);
	};
}
