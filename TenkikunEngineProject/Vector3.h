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

		Vector3 operator +(const Vector3& other) const;	//«΅Z
		Vector3 operator -(const Vector3& other) const;	//ψ«Z
		Vector3 operator *(const float& other) const;	//|―Z
		Vector3 operator /(const float& other) const;	//θZ

		Vector3& operator =(const Vector3& other);	//γό
		Vector3& operator +=(const Vector3& other);	//«΅Zγό
		Vector3& operator -=(const Vector3& other);	//ψ«Zγό
		Vector3& operator *=(const float& other);	//|―Zγό
		Vector3& operator /=(const float& other);	//θZγό

		Vector3 operator -() const;	//³½]

		bool operator ==(const Vector3& other) const;

		operator Vector2() const;	//Vector3©ηVector2ΦLXgΟ·

		const static Vector3 Zero();
		const static Vector3 One();

		const static Vector3 Right();
		const static Vector3 Left();
		const static Vector3 Up();
		const static Vector3 Down();
		const static Vector3 Forward();
		const static Vector3 Back();

		static float Distance(Vector3 vec1, Vector3 vec2);

		static Vector3 Cross(const Vector3& vec1, const Vector3& vec2);
		static float Dot(const Vector3& vec1, const Vector3& vec2);
};

