#pragma once
#include "Vector2.h"

class Vector2;
class Vector3
{
	public:
		float x;
		float y;
		float z;

		Vector3();
		Vector3(float x, float y, float z);

		float GetMagnitude();
		Vector3 GetNormalized();

		Vector3 operator +(const Vector3& other) const;	//�����Z
		Vector3 operator -(const Vector3& other) const;	//�����Z
		Vector3 operator *(const float& other) const;	//�|���Z
		Vector3 operator /(const float& other) const;	//����Z

		Vector3& operator =(const Vector3& other);	//���
		Vector3& operator +=(const Vector3& other);	//�����Z���
		Vector3& operator -=(const Vector3& other);	//�����Z���
		Vector3& operator *=(const float& other);	//�|���Z���
		Vector3& operator /=(const float& other);	//����Z���

		Vector3 operator -() const;	//�������]

		bool operator ==(const Vector3& other) const;

		operator Vector2() const;	//Vector3����Vector2�փL���X�g�ϊ�

		const static Vector3 Zero();
		const static Vector3 One();

		const static Vector3 Right();
		const static Vector3 Left();
		const static Vector3 Up();
		const static Vector3 Down();
		const static Vector3 Forward();
		const static Vector3 Back();

		static float Distance(Vector3 vec1, Vector3 vec2);

		//static float Cross(Vector3 vec1, Vector3 vec2);
		//static float Inner(Vector3 vec1, Vector3 vec2);

		//static bool IsCross(Vector3 p1, Vector3 p2, Vector3 p3, Vector3 p4, Vector3& crossPoint);
};

