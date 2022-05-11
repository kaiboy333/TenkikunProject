#include "Vector3.h"

Vector3::Vector3()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Vector3::Vector3(float x, float y, float z)
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

Vector3 Vector3::operator*(const float& other) const
{
    Vector3 vec;
    vec.x = this->x * other;
    vec.y = this->y * other;
    vec.z = this->z * other;
    return vec;
}

Vector3 Vector3::operator/(const float& other) const
{
    Vector3 vec;
    vec.x = this->x / other;
    vec.y = this->y / other;
    vec.z = this->z / other;
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

Vector3& Vector3::operator*=(const float& other)
{
    x *= other;
    y *= other;
    z *= other;
    return *this;
}

Vector3& Vector3::operator/=(const float& other)
{
    x /= other;
    y /= other;
    z /= other;
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

const Vector3 Vector3::Zero()
{
    return Vector3();
}

const Vector3 Vector3::One()
{
    return Vector3(1, 1, 1);
}

const Vector3 Vector3::Right()
{
    return Vector3(1, 0, 0);
}

const Vector3 Vector3::Left()
{
    return Vector3(-1, 0, 0);
}

const Vector3 Vector3::Up()
{
    return Vector3(0, 1, 0);
}

const Vector3 Vector3::Down()
{
    return Vector3(0, -1, 0);
}

const Vector3 Vector3::Forward()
{
    return Vector3(0, 0, 1);
}

const Vector3 Vector3::Back()
{
    return Vector3(0, 0, -1);
}
