#include "../include/vfrt/camera/camera.h"
#include <math.h>

static vec3 lowerLeftCorner(vec3 coord, vec3 horizontal, vec3 vertical, vec3 w, float focalLength)
{
    return subvec3(subvec3(subvec3(coord, sclmvec3(horizontal, 0.5f)), 
            sclmvec3(vertical, 0.5f)), sclmvec3(w, focalLength));
}

void initCameraRender(camera* c, int imageWidth, int imageHeight, float vfov, vec3 lookFromCam, vec3 lookAtCam, vec3 vup)
{
    c->lookFromCam = lookFromCam;
    c->lookAtCam = lookAtCam;
    c->vup = vup;

    c->imageWidth  = imageWidth;
    c->imageHeight = imageHeight;
    c->aspectRatio = (float)imageWidth / imageHeight;
    c->focalLength = length(subvec3(lookFromCam, lookAtCam));

    c->vfov = vfov;
    float theta = degreesToRadians(vfov);
    float h = tanf(theta / 2.0f);

    c->viewportHeight = 2.0f * h * c->focalLength;
    c->viewportWidth = c->viewportHeight * c->aspectRatio;

    c->w = normvec3(subvec3(lookFromCam, lookAtCam));
    c->u = normvec3(cross(vup, c->w));
    c->v = cross(c->w, c->u);

    c->coord = lookFromCam;
    c->horizontal = sclmvec3(c->u, c->viewportWidth);
    c->vertical = sclmvec3(c->v, -c->viewportHeight);

    c->lowerLeftCorner = lowerLeftCorner(c->coord, c->horizontal, c->vertical, c->w, c->focalLength);
}

ray setCameraGetRay(camera* c, float u, float v)
{
    vec3 direction = subvec3(addvec3(addvec3(c->lowerLeftCorner, sclmvec3(c->horizontal, u)), sclmvec3(c->vertical, v)), c->coord);
    return makeSetRay(c->coord, direction);
}
