#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include "Vector3.h"
#include <random>

class MyMath
{
	public:
		static float RadToEuler(float rad);	//���W�A������I�C���[��
		static float EulerToRad(float deg);

		static float Clamp(float value, float min, float max);

		static float Lerp(float min, float max, float t);

		//�����̌�������
		static bool IsCross(Vector3 vec1, Vector3 vec2, Vector3 vec3, Vector3 vec4, Vector3& crossPos);

		static int RandomRange(int min, int max);
		static float RandomRange(float min, float max);

	private:
		//�����_���������̏�����
		static std::random_device rd;
		static std::default_random_engine eng;
};

