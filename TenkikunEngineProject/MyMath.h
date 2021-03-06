#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include "Vector3.h"

class MyMath
{
	public:
		static float RadToEuler(float rad);	//ラジアンからオイラーへ
		static float EulerToRad(float deg);

		static float Clamp(float value, float min, float max);

		static float Lerp(float min, float max, float t);
};

