#pragma once

#include "prime_defines.h"

namespace prime {

	class Time
	{
	public:
		static void Init();

		static f64 Get();

		static void SetSleep(f64 miliSeconds);
	};

	class Timestep
	{
	private:
		f32 m_FrameTime = 0.0f;
		f32 m_DeltaTime = 0.0f;

	public:
		PINLINE f32 GetDT() const { return m_DeltaTime; }

		void Tick()
		{
			f32 time = (f32)Time::Get();
			m_DeltaTime = time - m_FrameTime;
			m_FrameTime = time;
		}
	};
}
