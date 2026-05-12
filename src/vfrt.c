#include "../include/vfrt/vfrt.h"
#include <stdint.h>

#define printRgbValues(r, g, b) printf("%d %d %d\n", (r), (g), (b))

#define ___VF_RAND
#ifdef  ___VF_RAND

static uint64_t hstate = 0x123456789abcdef0ULL;

static uint32_t uxorShift32(void)
{
    hstate = hstate ^ hstate << 13;
    hstate = hstate ^ hstate >> 7;
    hstate = hstate ^ hstate << 17;

    return (uint32_t)((hstate * 0x2545f4914f6cdd1dULL) >> 32);
}

float uxorShift32f(void)
{
    return (float)uxorShift32() * (1.0f / (float)0x100000000);
}

#endif // ___VF_RAND

void initRenderImg(int imageWidth, int imageHeight) 
{
    printf("P3\n");
    printf("%d %d\n", imageWidth, imageHeight);
    printf("255\n");
}

static void outFinalColor(vec3 color) 
{
    int r = (int)(255.999 * linearToSrgb(color.x));
    int g = (int)(255.999 * linearToSrgb(color.y));
    int b = (int)(255.999 * linearToSrgb(color.z));

    printRgbValues(r, g, b);
}

void renderSceneImg(camera* c, scene* s, int imageWidth, int imageHeight, int samples, int maxDepth)
{
    for (int j = 0; j < imageHeight; j++)
    {
        for (int i = 0; i < imageWidth; i++)
        {
            vec3 color = setvec3(0.0f, 0.0f, 0.0f);
            for (int sp = 0; sp < samples; sp++)
            {
                float u = ((float)i + uxorShift32f()) / (imageWidth - 1);
                float v = ((float)j + uxorShift32f()) / (imageHeight - 1);

                ray r = setCameraGetRay(c, u, v);
                color = addvec3(color, rayColor(&r, s, maxDepth));
            }

            color = sclmvec3(color, 1.0f / samples);
            outFinalColor(color);
        }
    }
}
