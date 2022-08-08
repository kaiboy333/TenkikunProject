#pragma once

#include <Windows.h>

class Time
{
	public:

		Time();

		static void Update();

		static float GetTime();
		static float GetDeltaTime();

	private:
		static const int FPS;
		static const float MIN_FRAME_TIME;
		static LARGE_INTEGER beforeTime;
		static LARGE_INTEGER nowTime;
		static LARGE_INTEGER timeFreq;

		static int frameCount;
		static double sumFPS;

		static float time;
		static float deltaTime;
};

