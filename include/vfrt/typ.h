#ifndef _V_F_RAYTRACER_TYPES_H
#define _V_F_RAYTRACER_TYPES_H

#include <stdbool.h>
#include "vec3/vec3.h"

typedef struct 
{
    vec3 origin;
    vec3 direction;
} ray;

typedef struct material material;

typedef struct 
{
    vec3     p;
    vec3     n;
    float    t;
    bool     f;
    material* mat;
} hrecord;

#define MSPHERES 512

#define _VF_MAX_NODES (MSPHERES * 2)
#define _VF_MAX_INDICES MSPHERES

typedef struct
{
    vec3 min;
    vec3 max;
} aabb;

typedef struct
{
    aabb box;
    int left;
    int right;
    int prims;
    int primc;
} bvhnode;

typedef struct 
{
    bvhnode n[_VF_MAX_NODES];
    int indice[_VF_MAX_INDICES];
    int ncount;
    int icount;
} bvh;

#endif