#pragma once

#include "prime_defines.h"
#include "prime_ref.h"

namespace prime {

	class Device;

	enum TextureFormat
	{
		TextureFormatNone,
		TextureFormatR8,
		TextureFormatRGB8,
		TextureFormatRGBA8,
		TextureFormatRGBA32F
	};

	struct TextureProperties
	{
		/**
		 * @brief Width of the texture.
		 */
		uint32_t width = 1;

		/**
		 * @brief Width of the texture.
		 */
		uint32_t height = 1;

		/**
		 * @brief Format of the texture.
		 */
		TextureFormat format = TextureFormatRGBA8;
	};

	class Texture2D
	{
		friend class Device;

	public:
		virtual ~Texture2D() {}

		/**
		 * @brief Bind the texture2d.
		 * @param slot The texture slot to bind the texture2d.
		 */
		virtual void Bind(u32 slot = 0) = 0;

		/**
		 * @brief Unbind the texture2d.
		 */
		virtual void Unbind() = 0;

        /**
		 * @brief Get the width of the texture2d.
		 * 
		 * @return u32 The width of the texture2d.
		 */
		virtual u32 GetWidth() const = 0;

		/**
		 * @brief Get the height of the texture2d.
		 * 
		 * @return u32 The height of the texture2d.
		 */
		virtual u32 GetHeight() const = 0;

		/**
		 * @brief Get the path of the texture2d.
		 * This returns the path if the texture2d was 
		 * loaded else returns an empty string if its was created.
		 * 
		 * @return str The path of the texture2d.
		 */
		virtual str GetPath() const = 0;

		/**
		 * @brief Get the handle of the texture2d.
		 * @return Texture2d handle
		 */
		virtual const void* GetHandle() const = 0;

	private:
		static Ref<Texture2D> Create(Device* device, const TextureProperties& props);
		static Ref<Texture2D> Create(Device* device, const str& filepath);
	};
}
