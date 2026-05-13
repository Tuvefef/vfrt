#define VF_CALC_EXEC_TIME_SCN
#include "../include/vfrt/vfrt.h"

#define IMGW 600
#define IMGH 356
#define SAMPLES 16
#define MAX_DEPTH 16

extern float uxorShift32f(void);

float uxorShift32fRange(float min, float max)
{
    return min + (max - min) * uxorShift32f();
}

static void scene0(scene* s)
{
    addElementInScene(s, setSphere(setvec3(0.0f, 0.0f, -1.0f), 0.5f, setDielectricMaterial(setvec3(1.0f, 1.0f, 1.0f), 1.50f)));
    addElementInScene(s, setSphere(setvec3(0.0f, -100.5f, -1.0f), 100.0f, setLambertianMaterial(setvec3(0.5f, 0.5f, 0.5f))));
    addElementInScene(s, setSphere(setvec3(-1.0f, 0.0f, -1.0f), 0.5f, setMetalMaterial(setvec3(0.4f, 0.8f, 0.6f), 0.5f)));
    addElementInScene(s, setSphere(setvec3(1.0f, 0.0f, -1.0f), 0.5f, setMetalMaterial(setvec3(0.7f, 0.5f, 0.6f), 0.2f)));
}

static void randomScene(scene* s)
{
    addElementInScene(s, setSphere(setvec3(0.0f, -1000.0f, 0.0f), 1000.0f, setLambertianMaterial(setvec3(0.5f, 0.5f, 0.5f))));

    for (int a = -11; a < 11; a++)
    {
        for (int b = -11; b < 11; b++)
        {
            float chooseMat = uxorShift32f();

            vec3 center = setvec3(a + 0.9f * uxorShift32f(), 0.2f, b + 0.9f * uxorShift32f());
            if (length(subvec3(center, setvec3(4.0f, 0.2f, 0.0f))) > 0.9f)
            {
                if (chooseMat < 0.8f)
                {
                    vec3 albedo = setvec3(
                        uxorShift32f() * uxorShift32f(),
                        uxorShift32f() * uxorShift32f(),
                        uxorShift32f() * uxorShift32f()
                    );

                    addElementInScene(s, setSphere(center, 0.2f, setLambertianMaterial(albedo)));
                }
                else if (chooseMat < 0.95f)
                {
                    vec3 albedo = setvec3(
                        uxorShift32fRange(0.5f, 1.0f),
                        uxorShift32fRange(0.5f, 1.0f),
                        uxorShift32fRange(0.5f, 1.0f)
                    );

                    float fuzz = uxorShift32fRange(0.0f, 0.5f);
                    addElementInScene(s, setSphere(center, 0.2f, setMetalMaterial(albedo, fuzz)));
                }
                else
                {
                    addElementInScene(s, setSphere(center, 0.2f, setDielectricMaterial(setvec3(1.0f, 1.0f, 1.0f), 1.5f)));
                }
            }
        }
    }

    addElementInScene(s, setSphere(setvec3(0.0f, 1.0f, 0.0f), 1.0f, setDielectricMaterial(setvec3(1.0f, 1.0f, 1.0f), 1.5f)));
    addElementInScene(s, setSphere(setvec3(-4.0f, 1.0f, 0.0f), 1.0f, setLambertianMaterial(setvec3(0.4f, 0.2f, 0.1f))));
    addElementInScene(s, setSphere(setvec3(4.0f, 1.0f, 0.0f), 1.0f, setMetalMaterial(setvec3(0.7f, 0.6f, 0.5f), 0.0f)));
}

static void cubeScene(scene* s)
{
    float spacing = 0.45f;
    for (int x = 0; x < 6; x++)
    {
        for (int y = 0; y < 6; y++)
        {
            for (int z = 0; z < 6; z++)
            {
                vec3 pos = setvec3((x - 3) * spacing, y * spacing, (z - 3) * spacing);
                vec3 color = setvec3(x / 6.0f, y / 6.0f, z / 6.0f);

                addElementInScene(s, setSphere(pos, 0.18f, setMetalMaterial(color, 0.05f)));
            }
        }
    }
}

int main() 
{
    initRenderImg(IMGW, IMGH);

    camera c;
    initCameraRender(&c, IMGW, IMGH, 50.0f, setvec3(-2.0f, 2.0f, 1.0f), setvec3(0.0f, 0.0f, -1.0f), setvec3(0.0f, 1.0f, 0.0f));

    scene s = {0};
    scene0(&s);
    renderSceneWithBvh(&s);

    calcSceneExecTime((void*)renderSceneImg, &c, &s, IMGW, IMGH, SAMPLES, MAX_DEPTH);

    return 0;
}