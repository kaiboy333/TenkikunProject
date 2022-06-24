#include "MyMath.h"

float MyMath::RadToEuler(float rad)
{
    return static_cast<float>(rad * 180.0f / M_PI);
}

float MyMath::EulerToRad(float deg)
{
    return static_cast<float>(deg * M_PI / 180.0f);
}

void MyMath::Clamp(float& value, float min, float max)
{
    if (value < min) {
        value = min;
    }
    else if (value > max) {
        value = max;
    }
}
