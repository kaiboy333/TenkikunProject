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

		//線分の交差判定
		static bool IsCross(Vector3 vec1, Vector3 vec2, Vector3 vec3, Vector3 vec4, Vector3& crossPos);
};

