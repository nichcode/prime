#pragma once

#include "prime_defines.h"
#include "prime_ref.h"

namespace prime {

	class Device;

	// more formats will be added
	enum TextureFormat
	{
		TextureFormatNone,
		TextureFormatR8,
		TextureFormatRGB8,
		TextureFormatRGBA8,
		TextureFormatRGBA32F
	};

	struct Texture2DHandle
	{
		void* Ptr = nullptr;
	};

	struct TextureProperties
	{
		uint32_t Width = 1;
		uint32_t Height = 1;
		TextureFormat Format = TextureFormatRGBA8;
	};

	class Texture2D
	{
	private:
		friend class Device;

	public:
		virtual ~Texture2D() {}

		virtual void Bind(u32 slot = 0) = 0;

		virtual u32 GetWidth() const = 0;
		virtual u32 GetHeight() const = 0;
		virtual str GetPath() const = 0;

	private:
		static Ref<Texture2D> Create(Device* device, const TextureProperties& props);
		static Ref<Texture2D> Create(Device* device, const str& filepath);
	};
}
