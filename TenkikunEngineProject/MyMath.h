#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include "Vector3.h"

class MyMath
{
	public:
		static float RadToEuler(float rad);	//ラジアンからオイラーへ
		static float EulerToRad(float deg);

		static void Clamp(float& value, float min, float max);
};

