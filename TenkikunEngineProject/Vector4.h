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

	//Vector4 operator +(const Vector4& other) const;	//�����Z
	//Vector4 operator -(const Vector4& other) const;	//�����Z
	//Vector4 operator *(const float& other) const;	//�|���Z
	//Vector4 operator /(const float& other) const;	//����Z

	//Vector4& operator =(const Vector4& other);	//���
	//Vector4& operator +=(const Vector4& other);	//�����Z���
	//Vector4& operator -=(const Vector4& other);	//�����Z���
	//Vector4& operator *=(const float& other);	//�|���Z���
	//Vector4& operator /=(const float& other);	//����Z���

	//Vector4 operator -() const;	//�������]



	//const static Vector4 Zero();
	//const static Vector4 One();

	//const static Vector4 Right();
	//const static Vector4 Left();
	//const static Vector4 Up();
	//const static Vector4 Down();
	//const static Vector4 Forward();
	//const static Vector4 Back();

};

