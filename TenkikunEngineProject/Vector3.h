#pragma once

class Vector3
{
	public:
		float x;
		float y;
		float z;

		Vector3();
		Vector3(float x, float y, float z);

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



		const static Vector3 Zero();
		const static Vector3 One();

		const static Vector3 Right();
		const static Vector3 Left();
		const static Vector3 Up();
		const static Vector3 Down();
		const static Vector3 Forward();
		const static Vector3 Back();

};

