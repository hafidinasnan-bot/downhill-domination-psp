
#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspgu.h>
#include <pspctrl.h>
#include <pspgum.h>

PSP_MODULE_INFO("Downhill PSP", 0, 1, 0);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 272

static unsigned int __attribute__((aligned(16))) list[262144];

void rectangle(float x1, float y1, float x2, float y2,
               unsigned int color)
{
    struct Vertex {
        float x, y, z;
        unsigned int color;
    };

    struct Vertex vertices[2] = {
        {x1, y1, 0, color},
        {x2, y2, 0, color}
    };

    sceGuDrawArray(
        GU_SPRITES,
        GU_VERTEX_32BITF | GU_COLOR_8888 | GU_TRANSFORM_2D,
        2, 0, vertices
    );
}

int main(void)
{
    sceGuInit();

    sceGuStart(GU_DIRECT, list);

    sceGuDrawBuffer(GU_PSM_8888, (void *)0, 512);
    sceGuDispBuffer(SCREEN_WIDTH, SCREEN_HEIGHT,
                    (void *)(512 * 272 * 4), 512);
    sceGuDepthBuffer((void *)(512 * 272 * 8), 512);

    sceGuOffset(2048 - (SCREEN_WIDTH / 2),
                2048 - (SCREEN_HEIGHT / 2));

    sceGuViewport(2048, 2048, SCREEN_WIDTH, SCREEN_HEIGHT);
    sceGuScissor(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    sceGuEnable(GU_SCISSOR_TEST);
    sceGuDisable(GU_DEPTH_TEST);
    sceGuDisable(GU_TEXTURE_2D);

    sceGuFinish();
    sceGuSync(0, 0);

    sceDisplayWaitVblankStart();
    sceGuDisplay(GU_TRUE);

    sceCtrlSetSamplingCycle(0);
    sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);

    float playerX = 240.0f;
    SceCtrlData pad;

    while (1)
    {
        sceCtrlPeekBufferPositive(&pad, 1);

        // Gerakan pemain ke kiri dan kanan
        if (pad.Buttons & PSP_CTRL_LEFT)
            playerX -= 3.0f;

        if (pad.Buttons & PSP_CTRL_RIGHT)
            playerX += 3.0f;

        // Batas gerakan pemain
        if (playerX < 80.0f)
            playerX = 80.0f;

        if (playerX > 400.0f)
            playerX = 400.0f;

        sceGuStart(GU_DIRECT, list);

        // Langit
        rectangle(0, 0, 480, 272,
                  GU_RGBA(90, 180, 240, 255));

        // Pegunungan
        rectangle(0, 95, 480, 150,
                  GU_RGBA(90, 120, 100, 255));

        // Tanah
        rectangle(0, 150, 480, 272,
                  GU_RGBA(40, 145, 55, 255));

        // Jalur downhill
        rectangle(125, 110, 355, 272,
                  GU_RGBA(110, 75, 45, 255));

        // Garis lintasan
        rectangle(235, 130, 245, 272,
                  GU_RGBA(230, 220, 180, 255));

        // Pohon kiri
        rectangle(35, 125, 55, 190,
                  GU_RGBA(100, 65, 30, 255));
        rectangle(10, 85, 80, 145,
                  GU_RGBA(20, 110, 35, 255));

        // Pohon kanan
        rectangle(410, 125, 430, 190,
                  GU_RGBA(100, 65, 30, 255));
        rectangle(385, 85, 455, 145,
                  GU_RGBA(20, 110, 35, 255));

        // Pemain sepeda sederhana
        rectangle(playerX - 12, 205,
                  playerX + 12, 232,
                  GU_RGBA(25, 25, 30, 255));

        rectangle(playerX - 20, 228,
                  playerX + 20, 235,
                  GU_RGBA(230, 35, 35, 255));

        rectangle(playerX - 10, 235,
                  playerX + 10, 265,
                  GU_RGBA(25, 25, 30, 255));

        sceGuFinish();
        sceGuSync(0, 0);

        sceDisplayWaitVblankStart();
        sceGuSwapBuffers();
    }

    sceGuTerm();
    sceKernelExitGame();

    return 0;
}
