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

	Vector2 operator +(const Vector2& other) const;	//‘«‚µZ
	Vector2 operator -(const Vector2& other) const;	//ˆø‚«Z
	Vector2 operator *(const float& other) const;	//Š|‚¯Z
	Vector2 operator /(const float& other) const;	//Š„‚èZ

	Vector2& operator =(const Vector2& other);	//‘ã“ü
	Vector2& operator +=(const Vector2& other);	//‘«‚µZ‘ã“ü
	Vector2& operator -=(const Vector2& other);	//ˆø‚«Z‘ã“ü
	Vector2& operator *=(const float& other);	//Š|‚¯Z‘ã“ü
	Vector2& operator /=(const float& other);	//Š„‚èZ‘ã“ü

	Vector2 operator -() const;	//³•‰”½“]

	bool operator ==(const Vector2& other) const;

	operator Vector3() const;	//Vector2‚©‚çVector3‚ÖƒLƒƒƒXƒg•ÏŠ·

	bool operator<(const Vector2& other) const;

	const static Vector2 Zero();
	const static Vector2 One();

	const static Vector2 Right();
	const static Vector2 Left();
	const static Vector2 Up();
	const static Vector2 Down();

	static float Distance(Vector2 vec1, Vector2 vec2);

	static float Cross(Vector2 vec1, Vector2 vec2);
	static float Dot(Vector2 vec1, Vector2 vec2);

	static bool IsCross(Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, Vector2& crossPoint);

	static float GetMinDistance(Vector2 p1, Vector2 p2, Vector2 targetPoint, Vector2& crossPoint);
};

