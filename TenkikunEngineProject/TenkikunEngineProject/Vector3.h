#pragma once
class Vector3
{
	public:
		float x;
		float y;
		float z;

		Vector3();
		Vector3(int x, int y, int z);

		Vector3 operator +(const Vector3& other) const;	//�����Z
		Vector3 operator -(const Vector3& other) const;	//�����Z

		Vector3& operator =(const Vector3& other);	//���
		Vector3& operator +=(const Vector3& other);	//�����Z���
		Vector3& operator -=(const Vector3& other);	//�����Z���

		Vector3 operator -() const;	//�������]

};

