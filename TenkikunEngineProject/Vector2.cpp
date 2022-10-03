#include "Vector2.h"
#include <cmath>
#include "DrawComponent.h"

Vector2::Vector2()
{
    this->x = 0;
    this->y = 0;
}

Vector2::Vector2(float x, float y)
{
    this->x = x;
    this->y = y;
}

float Vector2::GetMagnitude()
{
    //三平方の定理で長さを返す
    return std::sqrtf(std::powf(x, 2) + std::powf(y, 2));
}

Vector2 Vector2::GetNormalized()
{
    //長さを取得して
    float length = GetMagnitude();
    //それぞれのベクトルを長さで割る
    return Vector2(x / length, y / length);
}

//void Vector2::Draw(unsigned int color, Vector2 startPos)
//{
//    Vector2 drawStartPos = DrawComponent::GetDrawPos(startPos);
//    Vector2 drawPos = DrawComponent::GetDrawPos(*this + startPos);
//    DrawLineAA(drawStartPos.x, drawStartPos.y, drawPos.x, drawPos.y, color);
//}
//
//void Vector2::DrawPoint(unsigned int color)
//{
//    Vector2 drawPos = DrawComponent::GetDrawPos(*this);
//    DrawCircleAA(drawPos.x, drawPos.y, 5, 20, color);
//}

Vector2 Vector2::operator+(const Vector2& other) const
{
    Vector2 vec;
    vec.x = x + other.x;
    vec.y = y + other.y;
    return vec;
}

Vector2 Vector2::operator-(const Vector2& other) const
{
    Vector2 vec;
    vec.x = x - other.x;
    vec.y = y - other.y;
    return vec;
}

Vector2 Vector2::operator*(const float& other) const
{
    Vector2 vec;
    vec.x = this->x * other;
    vec.y = this->y * other;
    return vec;
}

Vector2 Vector2::operator/(const float& other) const
{
    Vector2 vec;
    vec.x = this->x / other;
    vec.y = this->y / other;
    return vec;
}

Vector2& Vector2::operator=(const Vector2& other)
{
    x = other.x;
    y = other.y;

    return *this;
}

Vector2& Vector2::operator+=(const Vector2& other)
{
    x += other.x;
    y += other.y;

    return *this;
}

Vector2& Vector2::operator-=(const Vector2& other)
{
    x -= other.x;
    y -= other.y;

    return *this;
}

Vector2& Vector2::operator*=(const float& other)
{
    x *= other;
    y *= other;
    return *this;
}

Vector2& Vector2::operator/=(const float& other)
{
    x /= other;
    y /= other;
    return *this;
}

Vector2 Vector2::operator-() const
{
    Vector2 vec;
    vec.x = -x;
    vec.y = -y;
    return vec;
}

bool Vector2::operator==(const Vector2& other) const
{
    return x == other.x && y == other.y;
}

Vector2::operator Vector3() const
{
    Vector3 vec;

    vec.x = this->x;
    vec.y = this->y;
    vec.z = 0;

    return vec;
}

const Vector2 Vector2::Zero()
{
    return Vector2();
}

const Vector2 Vector2::One()
{
    return Vector2(1, 1);
}

const Vector2 Vector2::Right()
{
    return Vector2(1, 0);
}

const Vector2 Vector2::Left()
{
    return Vector2(-1, 0);
}

const Vector2 Vector2::Up()
{
    return Vector2(0, 1);
}

const Vector2 Vector2::Down()
{
    return Vector2(0, -1);
}

float Vector2::Distance(Vector2 vec1, Vector2 vec2)
{
    return (vec2 - vec1).GetMagnitude();
}

float Vector2::Cross(Vector2 vec1, Vector2 vec2)
{
    return vec1.x * vec2.y - vec1.y * vec2.x;
}

float Vector2::Dot(Vector2 vec1, Vector2 vec2)
{
    return vec1.x * vec2.x + vec1.y * vec2.y;
}

bool Vector2::IsCross(Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, Vector2& crossPoint)
{
    float det = Cross(p2 - p1, p4 - p3);

    //平行じゃないなら
    if (det != 0) {
        float s = Cross(p3 - p1, p4 - p3) / det;
        float t = Cross(p2 - p1, p1 - p3) / det;

        //線分の交点なら
        if (s >= 0 && s <= 1 && t >= 0 && t <= 1) {
            crossPoint.x = p1.x + s * (p2 - p1).x;
            crossPoint.y = p1.y + s * (p2 - p1).y;

            return true;
        }
    }

    return false;
}

float Vector2::GetMinDistance(Vector2 p1, Vector2 p2, Vector2 targetPoint, Vector2& crossPoint)
{
    Vector2 p12 = p2 - p1;
    float a = std::powf(p12.GetMagnitude(), 2);

    if (a == 0) {
        return Vector2::Distance(p1, targetPoint);
    }

    float b = p12.x * (p1.x - targetPoint.x) + p12.y * (p1.y - targetPoint.y);
    float t = -(b / a);

    if (t < 0.0) {
        t = 0.0;
    }
    if (t > 1.0) {
        t = 1.0;
    }

    crossPoint.x = t * p12.x + p1.x;
    crossPoint.y = t * p12.y + p1.y;

    return Vector2::Distance(crossPoint, targetPoint);
}