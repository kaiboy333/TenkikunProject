#pragma once
class Vector3
{
	public:
		float x;
		float y;
		float z;

		Vector3();
		Vector3(int x, int y, int z);

		Vector3 operator +(const Vector3& other) const;	//‘«‚µZ
		Vector3 operator -(const Vector3& other) const;	//ˆø‚«Z

		Vector3& operator =(const Vector3& other);	//‘ã“ü
		Vector3& operator +=(const Vector3& other);	//‘«‚µZ‘ã“ü
		Vector3& operator -=(const Vector3& other);	//ˆø‚«Z‘ã“ü

		Vector3 operator -() const;	//³•‰”½“]

};

