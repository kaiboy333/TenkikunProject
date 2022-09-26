#pragma once
#include "Vector3.h"

class Vector2
{
public:
	float x;
	float y;

	Vector2();
	Vector2(float x, float y);

	float GetMagnitude();
	Vector2 GetNormalized();

	Vector2 operator +(const Vector2& other) const;	//�����Z
	Vector2 operator -(const Vector2& other) const;	//�����Z
	Vector2 operator *(const float& other) const;	//�|���Z
	Vector2 operator /(const float& other) const;	//����Z

	Vector2& operator =(const Vector2& other);	//���
	Vector2& operator +=(const Vector2& other);	//�����Z���
	Vector2& operator -=(const Vector2& other);	//�����Z���
	Vector2& operator *=(const float& other);	//�|���Z���
	Vector2& operator /=(const float& other);	//����Z���

	Vector2 operator -() const;	//�������]

	bool operator ==(const Vector2& other) const;

	operator Vector3() const;	//Vector3����Vector2�փL���X�g�ϊ�

	const static Vector2 Zero();
	const static Vector2 One();

	const static Vector2 Right();
	const static Vector2 Left();
	const static Vector2 Up();
	const static Vector2 Down();

	static float Distance(Vector2 vec1, Vector2 vec2);

	static float Cross(Vector2 vec1, Vector2 vec2);
	static float Inner(Vector2 vec1, Vector2 vec2);

	static bool IsCross(Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, Vector2& crossPoint);

	static float GetShortestDistance(Vector2 p1, Vector2 p2, Vector2 targetPoint, Vector2& crossPoint);
};

