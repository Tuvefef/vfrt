#ifndef _V_F_RAYTRACER_MATERIAL_H
#define _V_F_RAYTRACER_MATERIAL_H

#include "../typ.h"

struct material 
{
    bool (*scatter)(struct material* ms, ray* r, hrecord* h,
                    vec3* attenuation, ray* scatter);
    vec3 albedo;
    float fuzzReflection;
    float refractIndex;
};

typedef struct material material;
extern ray makeSetRay(vec3 origin, vec3 direction);

material setLambertianMaterial(vec3 albedo);
material setMetalMaterial(vec3 albedo, float fuzzReflection);
material setDielectricMaterial(vec3 albedo, float refractIndex);

#endif
