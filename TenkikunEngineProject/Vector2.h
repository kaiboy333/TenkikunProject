#pragma once
#include "Vector3.h"
#include "DxLib.h"

class Vector3;
class Vector2
{
public:
	float x;
	float y;

	Vector2();
	Vector2(float x, float y);

	float GetMagnitude() const;
	Vector2 GetNormalized() const;

	//void Draw(unsigned int color = GetColor(0, 0, 255), Vector2 startPos = Vector2::Zero());
	//void DrawPoint(unsigned int color = GetColor(0, 0, 255));

	Vector2 operator +(const Vector2& other) const;	//«΅Z
	Vector2 operator -(const Vector2& other) const;	//ψ«Z
	Vector2 operator *(const float& other) const;	//|―Z
	Vector2 operator /(const float& other) const;	//θZ

	Vector2& operator =(const Vector2& other);	//γό
	Vector2& operator +=(const Vector2& other);	//«΅Zγό
	Vector2& operator -=(const Vector2& other);	//ψ«Zγό
	Vector2& operator *=(const float& other);	//|―Zγό
	Vector2& operator /=(const float& other);	//θZγό

	Vector2 operator -() const;	//³½]

	bool operator ==(const Vector2& other) const;

	operator Vector3() const;	//Vector2©ηVector3ΦLXgΟ·

	bool operator<(const Vector2& other) const;

	const static Vector2 Zero();
	const static Vector2 One();

	const static Vector2 Right();
	const static Vector2 Left();
	const static Vector2 Up();
	const static Vector2 Down();

	static float Distance(const Vector2& vec1, const Vector2& vec2);

	static float Cross(const Vector2& vec1, const Vector2& vec2);
	static float Dot(const Vector2& vec1, const Vector2& vec2);

	static bool IsCross(const Vector2& p1, const Vector2& p2, const Vector2& p3, const Vector2& p4, Vector2& crossPoint);

	static float GetMinDistance(const Vector2& p1, const Vector2& p2, const Vector2& targetPoint, Vector2& crossPoint);
};

