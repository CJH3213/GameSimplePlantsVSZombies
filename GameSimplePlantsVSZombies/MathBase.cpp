#include "MathBase.h"

bool Math::NearZero(float f)
{
    return (f<EPSILON ? true : false);
}

double Math::ToDegrees(double radian)
{
    return (radian * RAD_TO_DEG);
}

