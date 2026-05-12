#ifndef _V_F_MATH_H
#define _V_F_MATH_H

#include <math.h>

#define inverseValue(x) (1.0f - (x))

#define PI 3.1415
#define EPSILON 1e-8f
#define INFINITYVAL 1e9f

static inline float degreesToRadians(float degrees)
{
    return degrees * PI / 180.0f;
}

static inline float linearToSrgb(float l)
{
    if (l <= 0.0031308f)
        return l * 12.92f;
    else
        return 1.055f * powf(l, 1.0f / 2.4f) - 0.055f;
}

#endif