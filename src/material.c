#include "../include/vfrt/material/material.h"
#include <math.h>

static bool lambertianScatter(struct material* ms, ray* r, hrecord* h, vec3* attenuation, ray* scatter)
{
    (void)r;
    vec3 direction = addvec3(h->n, randomNormVec());

    if (nearZero(direction))
        direction = h->n;

    *scatter = makeSetRay(h->p, direction);
    *attenuation = ms->albedo;
    
    return true;
}

static bool metalScatter(struct material* ms, ray* r, hrecord* h, vec3* attenuation, ray* scatter)
{
    vec3 reflected = reflect(normvec3(r->direction), h->n);
    reflected = addvec3(reflected, sclmvec3(randomNormVec(), ms->fuzzReflection));   

    *scatter = makeSetRay(h->p, reflected);
    *attenuation = ms->albedo;

    return dot(reflected, h->n) > 0;
}

static bool dielectricscatter(struct material* ms, ray* r, hrecord* h, vec3* attenuation, ray* scatter)
{
    *attenuation = ms->albedo;
    float ri = h->f ? (1.0f / ms->refractIndex) : ms->refractIndex;

    vec3 unitDirection = normvec3(r->direction);

    float ctheta = fmin(dot(setvec3(-unitDirection.x, -unitDirection.y, -unitDirection.z), h->n), 1.0f);
    float stheta = sqrtf(1.0f - ctheta * ctheta);

    bool cannotRefract = ri * stheta > 1.0f;
    vec3 direction;

    if (cannotRefract)
        direction = reflect(unitDirection, h->n);
    else 
        direction = refract(unitDirection, h->n, ri);

    *scatter = makeSetRay(h->p, direction);
    return true;
}

material setLambertianMaterial(vec3 albedo)
{
    material m = {.scatter = lambertianScatter, .albedo = albedo};   
    return m;
}

material setMetalMaterial(vec3 albedo, float fuzzReflection)
{
    material m = {.scatter = metalScatter, .albedo = albedo, .fuzzReflection = fuzzReflection};
    return m;
}

material setDielectricMaterial(vec3 albedo, float refractIndex)
{
    material m = {.scatter = dielectricscatter ,.albedo = albedo, .refractIndex = refractIndex};
    return m;
}
