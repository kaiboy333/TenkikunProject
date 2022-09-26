#include "Vector3.h"
#include <cmath>

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

float Vector3::GetMagnitude()
{
    //三平方の定理で長さを返す
    return std::sqrtf(std::powf(x, 2) + std::powf(y, 2) + std::powf(z, 2));
}

Vector3 Vector3::GetNormalized()
{
    //長さを取得して
    float length = GetMagnitude();
    //それぞれのベクトルを長さで割る
    return Vector3(x / length, y / length, z / length);
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
    vec.x = -x;
    vec.y = -y;
    vec.z = -z;
    return vec;
}

bool Vector3::operator==(const Vector3& other) const
{
    return x == other.x && y == other.y && z == other.z;
}

Vector3::operator Vector2() const
{
    Vector3 vec;

    vec.x = this->x;
    vec.y = this->y;
    vec.z = 0;

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

float Vector3::Distance(Vector3 vec1, Vector3 vec2)
{
    return (vec2 - vec1).GetMagnitude();
}

//float Vector3::Cross(Vector3 vec1, Vector3 vec2)
//{
//    return vec1.x * vec2.y - vec1.y * vec2.x;
//}
//
//float Vector3::Inner(Vector3 vec1, Vector3 vec2)
//{
//    return vec1.x * vec2.x + vec1.y * vec2.y;
//}
//
//bool Vector3::IsCross(Vector3 p1, Vector3 p2, Vector3 p3, Vector3 p4, Vector3& crossPoint)
//{
//    float det = Cross(p2 - p1, p4 - p3);
//
//    //平行じゃないなら
//    if (det != 0) {
//        float s = Cross(p3 - p1, p4 - p3) / det;
//        float t = Cross(p2 - p1, p1 - p3) / det;
//
//        //線分の交点なら
//        if (s >= 0 && s <= 1 && t >= 0 && t <= 1) {
//            crossPoint.x = p1.x + s * (p2 - p1).x;
//            crossPoint.y = p1.y + s * (p2 - p1).y;
//            crossPoint.z = 0;
//
//            return true;
//        }
//    }
//
//    return false;
//}
