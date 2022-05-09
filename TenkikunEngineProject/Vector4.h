#pragma once

class Vector4
{
public:
	float x;
	float y;
	float z;
	float w;

	Vector4();
	Vector4(float x, float y, float z, float w);

	//Vector4 operator +(const Vector4& other) const;	//‘«‚µZ
	//Vector4 operator -(const Vector4& other) const;	//ˆø‚«Z
	//Vector4 operator *(const float& other) const;	//Š|‚¯Z
	//Vector4 operator /(const float& other) const;	//Š„‚èZ

	//Vector4& operator =(const Vector4& other);	//‘ã“ü
	//Vector4& operator +=(const Vector4& other);	//‘«‚µZ‘ã“ü
	//Vector4& operator -=(const Vector4& other);	//ˆø‚«Z‘ã“ü
	//Vector4& operator *=(const float& other);	//Š|‚¯Z‘ã“ü
	//Vector4& operator /=(const float& other);	//Š„‚èZ‘ã“ü

	//Vector4 operator -() const;	//³•‰”½“]



	//const static Vector4 Zero();
	//const static Vector4 One();

	//const static Vector4 Right();
	//const static Vector4 Left();
	//const static Vector4 Up();
	//const static Vector4 Down();
	//const static Vector4 Forward();
	//const static Vector4 Back();

};

