#ifndef _V_F_RAYTRACER_VEC3_H
#define _V_F_RAYTRACER_VEC3_H

#include <math.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <stdlib.h>

extern float uxorShift32f(void);

typedef struct 
{
  	float x;
  	float y;
	float z;
} vec3;

static inline vec3 setvec3(float x, float y, float z) 
{
	return (vec3){x, y, z}; 
}

static inline vec3 addvec3(const vec3 v0, const vec3 v1) 
{
	return setvec3(v0.x + v1.x, v0.y + v1.y, v0.z + v1.z);
}

static inline vec3 subvec3(const vec3 v0, const vec3 v1) 
{
	return setvec3(v0.x - v1.x, v0.y - v1.y, v0.z - v1.z);
}

static inline vec3 mulvec3(const vec3 v0, const vec3 v1) 
{
	return setvec3(v0.x * v1.x, v0.y * v1.y, v0.z * v1.z);
}

static inline vec3 sclmvec3(const vec3 v, float x) 
{
	return setvec3(v.x * x, v.y * x, v.z * x);
}

static inline vec3 divvec3(const vec3 v0, const vec3 v1) 
{
	return setvec3(v0.x / v1.x, v0.y / v1.y, v0.z / v1.z);
}

static inline float dot(const vec3 v0, const vec3 v1)
{
	return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z;
}

static inline vec3 cross(const vec3 v0, const vec3 v1)
{
	return setvec3(
		v0.y * v1.z - v0.z * v1.y,
		v0.z * v1.x - v0.x * v1.z,
		v0.x * v1.y - v0.y * v1.x
	);
}

static inline vec3 normvec3(vec3 v)
{
    float len = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
    return setvec3(v.x / len, v.y / len, v.z / len);
}

static inline vec3 reflect(const vec3 v, const vec3 n)
{
    return subvec3(v, sclmvec3(n, 2.0f * dot(v, n)));
}

static inline float slength(const vec3 v)
{
    return v.x * v.x + v.y * v.y + v.z * v.z;
}

static inline vec3 refract(const vec3 v, const vec3 n, float eta)
{
    float ctheta = fmin(dot(setvec3(-v.x, -v.y, -v.z), n), 1.0f);
    
    vec3 rouperp = sclmvec3(addvec3(v, sclmvec3(n, ctheta)), eta);
    vec3 rouprll = sclmvec3(n, -sqrtf(fabsf(1.0f - slength(rouperp))));

    return addvec3(rouperp, rouprll);
}

static inline float length(vec3 v)
{
	return sqrtf(dot(v, v));
}

static inline vec3 randomVec3(float min, float max) 
{
    float range = max - min;
    return setvec3(
        min + uxorShift32f() * range,
        min + uxorShift32f() * range,
        min + uxorShift32f() * range
    );
}

static inline vec3 randomInNormSphere(void) 
{
    while (1) 
	{
        vec3 p = randomVec3(-1.0f, 1.0f);
        if (dot(p, p) < 1.0f)
            return p;
    }
}

static inline vec3 randomNormVec(void) 
{
    return normvec3(randomInNormSphere());
}

static inline bool nearZero(vec3 v) 
{
    float e = 1e-8f;
    return (fabsf(v.x) < e) && (fabsf(v.y) < e) && (fabsf(v.z) < e);
}

#endif
