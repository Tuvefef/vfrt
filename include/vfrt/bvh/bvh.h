#ifndef _V_F_RAYTRACER_BVH_H
#define _V_F_RAYTRACER_BVH_H

#include <float.h>
#include "../typ.h"
#include "../scene/sphere.h"

extern bool hittRenderSphere(sphere* s, ray* r, float tmin, float tmax, hrecord* h);
static const sphere* gSphereForSort = NULL;

static inline aabb sphereBounds(sphere* s)
{
    aabb b;
    vec3 r = setvec3(s->radius, s->radius, s->radius);
    b.min = subvec3(s->coord, r);
    b.max = addvec3(s->coord, r);
    return b;
}

static inline aabb aabbUnion(aabb a, aabb b)
{
    aabb r;

    r.min = setvec3(
        fminf(a.min.x, b.min.x),
        fminf(a.min.y, b.min.y),
        fminf(a.min.z, b.min.z)
    );

    r.max = setvec3(
        fmaxf(a.max.x, b.max.x),
        fmaxf(a.max.y, b.max.y),
        fmaxf(a.max.z, b.max.z)
    );

    return r;
}

static inline aabb computeBounds(sphere* s, int* indices, int count)
{
    aabb b;
    b.min = setvec3(FLT_MAX, FLT_MAX, FLT_MAX);
    b.max = setvec3(-FLT_MAX, -FLT_MAX, -FLT_MAX);

    for (int i = 0; i < count; i++)
    {
        b = aabbUnion(b, sphereBounds(&s[indices[i]]));
    }

    return b;
}

static inline int longAxis(aabb b)
{
    float dx = b.max.x - b.min.x;
    float dy = b.max.y - b.min.y;
    float dz = b.max.z - b.min.z;

    if (dx >= dy && dx >= dz)
        return 0;
    
    if (dy >= dz)
        return 1;

    return 2;
}

static inline int cmpx(const void* a, const void* b)
{
    float ca = gSphereForSort[*(int*)a].coord.x;
    float cb = gSphereForSort[*(int*)b].coord.x;

    return (ca > cb) - (ca < cb);
}

static inline int cmpy(const void* a, const void* b)
{
    float ca = gSphereForSort[*(int*)a].coord.y;
    float cb = gSphereForSort[*(int*)b].coord.y;

    return (ca > cb) - (ca < cb);
}

static inline int cmpz(const void* a, const void* b)
{
    float ca = gSphereForSort[*(int*)a].coord.z;
    float cb = gSphereForSort[*(int*)b].coord.z;

    return (ca > cb) - (ca < cb);
}

static inline int buildRecursive(bvh* b, sphere* s, int istart, int count, int depth)
{
    int nodeid = b->ncount++;
    bvhnode* node = &b->n[nodeid];

    node->box = computeBounds(s, b->indice + istart, count);
    if (count <= 4 || depth >= 20) 
    {
        node->left = -1;
        node->right = -1;
        node->prims = istart;
        node->primc = count;
        return nodeid;
    }

    int axis = longAxis(node->box);
    gSphereForSort = s;

    int (*cmp)(const void*, const void*) = (axis == 0) ? cmpx : (axis == 1) ? cmpy : cmpz;
    qsort(b->indice + istart, count, sizeof(int), cmp);
    int half = count / 2;

    node->primc = 0;
    node->left  = buildRecursive(b, s, istart, half, depth + 1);
    node->right = buildRecursive(b, s, istart + half, count - half, depth + 1);

    return nodeid;
}

static inline void bvhBuild(bvh* b, sphere* spheres, int count)
{
    b->ncount = 0;
    b->icount = count;

    for (int i = 0; i < count; i++)
        b->indice[i] = i;

    if (count > 0)
        buildRecursive(b, spheres, 0, count, 0);
}

static inline int rayAabb(const ray* r, aabb box, float tmin, float tmax)
{
    float inv[3] = {
        1.0f / r->direction.x,
        1.0f / r->direction.y,
        1.0f / r->direction.z
    };

    float orig[3] = {r->origin.x, r->origin.y, r->origin.z};
    float bmin[3] = {box.min.x, box.min.y, box.min.z};
    float bmax[3] = {box.max.x, box.max.y, box.max.z};

    for (int a = 0; a < 3; a++) 
    {
        float t0 = (bmin[a] - orig[a]) * inv[a];
        float t1 = (bmax[a] - orig[a]) * inv[a];

        if (inv[a] < 0.0f) 
        { 
            float tmp = t0; 
            t0 = t1; 
            t1 = tmp; 
        }

        tmin = t0 > tmin ? t0 : tmin;
        tmax = t1 < tmax ? t1 : tmax;

        if (tmax <= tmin) 
            return 0;
    }

    return 1;
}

static inline int bvhHitt(bvh* b, sphere* s, ray* r, hrecord* h, float tmin, float tmax)
{
    int stack[64];
    int top = 0;
    int found = 0;
    float closest = tmax;

    stack[top++] = 0;

    while (top > 0)
    {
        const bvhnode* node = &b->n[stack[--top]];

        if (!rayAabb(r, node->box, tmin, closest))
            continue;

        if (node->primc > 0)
        {
            for (int i = 0; i < node->primc; i++)
            {
                int si = b->indice[node->prims + i];
                hrecord tmp;
                if (hittRenderSphere(&s[si], r, tmin, closest, &tmp))
                {
                    found = 1;
                    closest = tmp.t;
                    *h = tmp;
                }
            }
        }
        else 
        {
            stack[top++] = node->left;
            stack[top++] = node->right;
        }
    }

    return found;
}

#endif