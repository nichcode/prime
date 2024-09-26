#pragma once

#include "prime_defines.h"

namespace prime {

	class Device;

	class Time
	{
		friend class Device;
	public:
        /**
         * @brief Get the current time.
         * 
         * @return f64 the current time.
         */
		static f64 Get();

        /**
         * @brief sleep for an amount of milliseconds.
         * 
         * @param miliSeconds the amount of milliseconds to sleep .
         */
		static void SetSleep(f64 miliSeconds);

	private:
		/**
		 * @brief Initialize the time subsystem. This is called by the device.
		 */
		static void Init();
	};

	class Timestep
	{
	private:
		f32 m_FrameTime = 0.0f;
		f32 m_DeltaTime = 0.0f;

	public:
	    /**
	     * @brief get the delta time.
	     * 
	     * @return PINLINE the delta time.
	     */
		PINLINE f32 GetDT() const { return m_DeltaTime; }

		/**
		 * @brief Update the step on the current frame.
		 */
		void Tick()
		{
			f32 time = (f32)Time::Get();
			m_DeltaTime = time - m_FrameTime;
			m_FrameTime = time;
		}
	};
}
