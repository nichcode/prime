#pragma once

#include "prime_defines.h"
#include "prime_vertexbuffer.h"
#include "prime_ref.h"
#include "prime_driver_types.h"
#include "prime_indexbuffer.h"
#include "prime_shader.h"
#include "prime_uniformbuffer.h"
#include "prime_texture.h"
#include "prime_render_target.h"
#include "prime_context.h"

namespace prime {

	class Window;

	class Device
	{
	private:
		DriverTypes m_type;

	public:
		Device() : m_type(DriverTypesNone) { }

		Device(const Device&) = delete;
		Device& operator=(const Device&) = delete;

        /**
         * @brief Initialize the device and its subsystems.
         * @param type The driver type ie. opengl, directx11 etc.
         */
		void Init(DriverTypes type);

        /**
         * @brief Get the driver type of the device.
         * 
         * @return PINLINE the driver type.
         */
		PINLINE DriverTypes GetType() const { return m_type; }

		/**
		 * @brief Create a rendering context. The device keeps the object itself and
		 * returns reference to the caller of the function. The helps to clean up all sunresources created.
		 * @return void* The driver handle of the device.
		 */
		Ref<Context> CreateContext(Window* window);

		/**
		 * @brief Create a vertexbuffer object. The device keeps the object itself and
		 * returns reference to the caller of the function. The helps to clean up all sunresources created.
		 * 
		 * @param data The data for the vertexbuffer. This can be a nullptr.
		 * @param size The size of the vertexbuffer.
		 * @param type The type of the vertexbuffer ie. static or dynamic.
		 * @return Ref<Vertexbuffer> the reference of the vertexbuffer if it was created else nullptr.
		 */
		Ref<Vertexbuffer> CreateVertexBuffer(const void* data, u32 size, VertexbufferType type);
        
		/**
		 * @brief Create a indexbuffer object. The device keeps the object itself and
		 * returns reference to the caller of the function. The helps to clean up all sunresources created.
		 * 
		 * @param indices the indices which the index buffer will stored and use. 
		 * Prime supports only 32bit indices.
		 * @param count The count of the indices.
		 * @return Ref<Indexbuffer> The reference of the indexbuffer if it was created else nullptr.
		 */
		Ref<Indexbuffer> CreateIndexBuffer(u32* indices, u32 count);

		/**
		 * @brief Create a shader object. The device keeps the object itself and
		 * returns reference to the caller of the function. The helps to clean up all sunresources created.
		 * 
		 * @param VSource The vertexshader source to use.
		 * @param PSource The pixelshader source to use.
		 * @param load If true the Vsource and PSource will be loaded as files from disk.
		 * @return Ref<Shader> The reference of the shader if it was created else nullptr.
		 */
		Ref<Shader> CreateShader(const str& VSource, const str& PSource, b8 load);

		/**
		 * @brief Create a uniformbuffer object. The device keeps the object itself and
		 * returns reference to the caller of the function. The helps to clean up all sunresources created.
		 * 
		 * @param size The size of the uniformbuffer.
		 * @param binding The binding slot to use for the uniform buffer.
		 * @return Ref<Uniformbuffer> The reference of the uniformbuffer if it was created else nullptr.
		 */
		Ref<Uniformbuffer> CreateUniformbuffer(u32 size, u32 binding);

		/**
		 * @brief Create a Texture2d object. The device keeps the object itself and
		 * returns reference to the caller of the function. The helps to clean up all sunresources created.
		 * 
		 * @param props The properties of the texture2d.
		 * @return Ref<Texture2D> The reference of the texture2d if it was created else nullptr.
		 */
		Ref<Texture2D> CreateTexture2D(const TextureProperties& props);

		/**
		 * @brief Load a Texture2d object. The device keeps the object itself and
		 * returns reference to the caller of the function. The helps to clean up all sunresources created.
		 * 
		 * @param filepath The filepath to load the texture2d.
		 * @return Ref<Texture2D> The reference of the texture2d if it was created else nullptr.
		 */
		Ref<Texture2D> CreateTexture2D(const str& filepath);

		/**
		 * @brief Create a rendertarget object. The device keeps the object itself and
		 * returns reference to the caller of the function. The helps to clean up all sunresources created.
		 * 
		 * @param width The width of the rendertarget.
		 * @param height The height of the rendertarget.
		 * @param viewport A pointer to the viewport of the device.
		 * @return Ref<RenderTarget> The reference of the rendertarget if it was created else nullptr.
		 */
		Ref<RenderTarget> CreateRenderTarget(u32 width, u32 height, const Viewport* viewport);
	};
}
