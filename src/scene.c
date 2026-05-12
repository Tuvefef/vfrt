#include "../include/vfrt/scene/scene.h"
#include <float.h>

static vec3 at(float t, ray* r)
{
    return addvec3(r->origin, sclmvec3(r->direction, t));
}

bool hittRenderSphere(sphere* s, ray* r, float tmin, float tmax, hrecord* h)
{
    vec3 oc = subvec3(s->coord, r->origin);

    float a = dot(r->direction, r->direction);
    float b = -2.0f * dot(r->direction, oc);
    float c = dot(oc, oc) - s->radius * s->radius;
    float d = b * b - 4.0f * a * c;

    if (d < 0.0f)
        return false;

    float sq = sqrtf(d);
    float rt = (-b - sq) / (2.0f * a);

    if (rt <= tmin || rt >= tmax)
    {
        rt = (-b + sq) / (2.0f * a);
        if (rt <= tmin || rt >= tmax)
            return false;
    }

    h->t = rt;
    h->p = at(rt, r);

    vec3 outwardNormal = sclmvec3(subvec3(h->p, s->coord), 1.0f / s->radius);

    h->f = dot(r->direction, outwardNormal) < 0.0f;
    h->n = h->f ? outwardNormal : sclmvec3(outwardNormal, -1.0f);
    h->mat = &s->mat;

    return true;
}

#ifdef VF_INC_BVH
void renderSceneWithBvh(scene* s)
{
    bvhBuild(&s->tree, s->s, s->count);
    s->bvhb = 1;
}
#endif

static bool hittRenderScene(scene* sn, ray* r, float tmin, float tmax, hrecord* h)
{

#ifdef VF_INC_BVH
    if (sn->bvhb)
        return bvhHitt(&sn->tree, sn->s, r, h, tmin, tmax);
#endif

    hrecord ht;
    bool hitAnything = false;
    float closest = tmax;

    for (int i = 0; i < sn->count; i++)
    {
        if (hittRenderSphere(&sn->s[i], r, tmin, closest, &ht))
        {
            hitAnything = true;
            closest = ht.t;
            *h = ht;
        }
    }
    return hitAnything;
}

ray makeSetRay(vec3 origin, vec3 direction)
{
    ray r = {.origin = origin, .direction = direction};
    return r;
}

void addElementInScene(scene* sn, sphere sp)
{
    if (sn->count < MSPHERES)
        sn->s[sn->count++] = sp;
}

sphere setSphere(vec3 coord, float radius, material mat)
{
    sphere s = { .coord = coord, .radius = radius, .mat = mat };
    return s;
}

vec3 rayColor(ray* r, scene* s, float depth)
{
    if (depth <= 0.0f)
        return setvec3(0.0f, 0.0f, 0.0f);

    hrecord h;

    if (hittRenderScene(s, r, 0.001f, INFINITYVAL, &h))
    {
        ray  scattered;
        vec3 attenuation;

        if (h.mat->scatter(h.mat, r, &h, &attenuation, &scattered))
        {
            vec3 bounced = rayColor(&scattered, s, depth - 1.0f);
            return setvec3(
                attenuation.x * bounced.x,
                attenuation.y * bounced.y,
                attenuation.z * bounced.z
            );
        }
        return setvec3(0.0f, 0.0f, 0.0f);
    }

    vec3 unitDirection = normvec3(r->direction);
    float t = 0.5f * (unitDirection.y + 1.0f);
    return addvec3(
        sclmvec3(setvec3(1.0f, 1.0f, 1.0f), inverseValue(t)),
        sclmvec3(setvec3(0.5f, 0.7f, 1.0f), t)
    );
}