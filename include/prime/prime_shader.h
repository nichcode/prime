#pragma once

#include "prime_defines.h"
#include "prime_ref.h"

namespace prime {

	class Device;

	class Shader
	{
		friend class Device;

	public:
		virtual ~Shader() {}

		/**
		 * @brief Bind the shader.
		 */
		virtual void Bind() = 0;

		/**
		 * @brief Unbind the shader.
		 */
		virtual void Unbind() = 0;
        
		/**
		 * @brief Set an interger.
		 * 
		 * @param name The name of the layout location to set the data.
		 * @param data The integer to set.
		 */
		virtual void SetInt(const str& name, i32 data) = 0;

		/**
		 * @brief Set an interger array.
		 * 
		 * @param name The name of the layout location to set the data.
		 * @param data The interger array to set.
		 * @param count The number of the intergers in interget array.
		 */
		virtual void SetIntArray(const str& name, i32* data, u32 count) = 0;

        /**
         * @brief Set a float.
         * 
         * @param name The name of the layout location to set the data.
         * @param data The float to set.
         */
		virtual void SetFloat(const str& name, f32 data) = 0;

        /**
         * @brief Set two floats.
         * 
         * @param name The name of the layout location to set the data.
         * @param data The first float to set.
         * @param data2 The second float to set.
         */
		virtual void SetFloat2(const str& name, f32 data, f32 data2) = 0;

		/**
		 * @brief Set three floats.
		 * 
		 * @param name The name of the layout location to set the data.
		 * @param data The first float to set.
		 * @param data2 The second float to set.
		 * @param data3 The third float to set.
		 */
		virtual void SetFloat3(const str& name, f32 data, f32 data2, f32 data3) = 0;

		/**
		 * @brief Set four floats.
		 * 
		 * @param name The name of the layout location to set the data.
		 * @param data The first float to set.
		 * @param data2 The second float to set.
		 * @param data3 The third float to set.
		 * @param data4 The fourth float to set.
		 */
		virtual void SetFloat4(const str& name, f32 data, f32 data2, f32 data3, f32 data4) = 0;

        /**
         * @brief Set a 2x2 matrix.
         * 
         * @param name The name of the layout location to set the data.
         * @param data A pointer to an array of floats ie. data[2][2].
         */
		virtual void SetMat2(const str& name, f32* data) = 0;

		/**
		 * @brief Set a 3x3 matrix.
		 * 
		 * @param name The name of the layout location to set the data.
		 * @param data A pointer to an array of floats ie. data[3][3].
		 */
		virtual void SetMat3(const str& name, f32* data) = 0;

		/**
		 * @brief Set a 4x4 matrix.
		 * 
		 * @param name The name of the layout location to set the data.
		 * @param data A pointer to an array of floats ie. data[4][4].
		 */
		virtual void SetMat4(const str& name, f32* value) = 0;

	private:
		static Ref<Shader> Create(Device* devide, const str& vSource, const str& pSource, b8 load);
	};
}
