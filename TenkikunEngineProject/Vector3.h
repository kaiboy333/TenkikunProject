#pragma once

class Vector3
{
	public:
		float x;
		float y;
		float z;

		Vector3();
		Vector3(float x, float y, float z);

		Vector3 operator +(const Vector3& other) const;	//‘«‚µZ
		Vector3 operator -(const Vector3& other) const;	//ˆø‚«Z
		Vector3 operator *(const float& other) const;	//Š|‚¯Z
		Vector3 operator /(const float& other) const;	//Š„‚èZ

		Vector3& operator =(const Vector3& other);	//‘ã“ü
		Vector3& operator +=(const Vector3& other);	//‘«‚µZ‘ã“ü
		Vector3& operator -=(const Vector3& other);	//ˆø‚«Z‘ã“ü
		Vector3& operator *=(const float& other);	//Š|‚¯Z‘ã“ü
		Vector3& operator /=(const float& other);	//Š„‚èZ‘ã“ü

		Vector3 operator -() const;	//³•‰”½“]



		const static Vector3 Zero();
		const static Vector3 One();

		const static Vector3 Right();
		const static Vector3 Left();
		const static Vector3 Up();
		const static Vector3 Down();
		const static Vector3 Forward();
		const static Vector3 Back();

};

