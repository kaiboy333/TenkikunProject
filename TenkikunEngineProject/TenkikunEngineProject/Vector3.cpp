#include "Vector3.h"

Vector3::Vector3()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Vector3::Vector3(int x, int y, int z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3 Vector3::operator+(const Vector3& other) const
{
    Vector3 vec;
    vec.x = x + other.x;
    vec.y = y + other.y;
    vec.z = z + other.z;
    return vec;
}

Vector3 Vector3::operator-(const Vector3& other) const
{
    Vector3 vec;
    vec.x = x - other.x;
    vec.y = y - other.y;
    vec.z = z - other.z;
    return vec;
}

Vector3& Vector3::operator=(const Vector3& other)
{
    x = other.x;
    y = other.y;
    z = other.z;

    return *this;
}

Vector3& Vector3::operator+=(const Vector3& other)
{
    x += other.x;
    y += other.y;
    z += other.z;

    return *this;
}

Vector3& Vector3::operator-=(const Vector3& other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;

    return *this;
}

Vector3 Vector3::operator-() const
{
    Vector3 vec;
    vec.x = x;
    vec.y = y;
    vec.z = z;
    return vec;
}
