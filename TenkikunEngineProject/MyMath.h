#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

class MyMath
{
	public:
		static float RadToEuler(float rad);	//ラジアンからオイラーへ
		static float EulerToRad(float deg);
};

