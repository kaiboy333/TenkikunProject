#include "MyMath.h"

float MyMath::RadToEuler(float rad)
{
    return rad * 180.0f / M_PI;
}

float MyMath::EulerToRad(float deg)
{
    return deg * M_PI / 180.0f;
}
