#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include "Vector3.h"
#include <random>
#include <numbers>

class MyMath
{
	public:
		static const float PI;
		static const float RAD_TO_DEG;
		static const float DEG_TO_RAD;

		static float RadToEuler(float rad);	//ラジアンからオイラーへ
		static float EulerToRad(float deg);

		static float Clamp(float value, float min, float max);

		static float Lerp(float min, float max, float t);

		//線分の交差判定
		static bool IsCross(Vector2 vec1, Vector2 vec2, Vector2 vec3, Vector2 vec4, Vector2& crossPos);

		//min以上max未満
		static int RandomRange(int minInclusive, int maxExclusive);
		//min以上max以下
		static float RandomRange(float minInclusive, float maxInclusive);

	private:
		//ランダム生成期の初期化
		static std::random_device rd;
		static std::default_random_engine eng;
};