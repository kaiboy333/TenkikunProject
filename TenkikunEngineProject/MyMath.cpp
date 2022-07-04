#include "MyMath.h"

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
