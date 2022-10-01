#include "MyMath.h"
#include "Vector2.h"

float MyMath::RadToEuler(float rad)
{
    return static_cast<float>(rad * 180.0f / M_PI);
}

float MyMath::EulerToRad(float deg)
{
    return static_cast<float>(deg * M_PI / 180.0f);
}

float MyMath::Clamp(float value, float min, float max)
{
    if (value < min) {
        value = min;
    }
    else if (value > max) {
        value = max;
    }

    return value;
}

float MyMath::Lerp(float min, float max, float t)
{
    //t‚Í0`1‚Ì”ÍˆÍ
    t = Clamp(t, 0, 1);

    return min + (max - min) * t;
}

bool MyMath::IsCross(Vector2 vec1, Vector2 vec2, Vector2 vec3, Vector2 vec4, Vector2& crossPos)
{
    float d = (vec2.x - vec1.x) * (vec4.y - vec3.y) - (vec2.y - vec1.y) * (vec4.x - vec3.x);

    if (d == 0.0f)
    {
        return false;
    }

    float u = ((vec3.x - vec1.x) * (vec4.y - vec3.y) - (vec3.y - vec1.y) * (vec4.x - vec3.x)) / d;
    float v = ((vec3.x - vec1.x) * (vec2.y - vec1.y) - (vec3.y - vec1.y) * (vec2.x - vec1.x)) / d;

    if (u < 0.0f || u > 1.0f || v < 0.0f || v > 1.0f)
    {
        return false;
    }

    crossPos.x = vec1.x + u * (vec2.x - vec1.x);
    crossPos.y = vec1.y + u * (vec2.y - vec1.y);

    return true;
}

int MyMath::RandomRange(int min, int max)
{
    std::uniform_int_distribution<int> distr(min, max);
    return distr(eng);
}

float MyMath::RandomRange(float min, float max)
{
    std::uniform_real_distribution<float> distr(min, max);
    return distr(eng);
}

//ƒ‰ƒ“ƒ_ƒ€¶¬Šú‚Ì‰Šú‰»
std::random_device MyMath::rd;
std::default_random_engine MyMath::eng(MyMath::rd());


