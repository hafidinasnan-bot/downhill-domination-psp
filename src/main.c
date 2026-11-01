
#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspgu.h>
#include <pspdebug.h>
#include <pspctrl.h>

PSP_MODULE_INFO("Downhill Prototype", 0, 1, 0);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

#define W 480
#define H 272
#define BUF 512

static unsigned int __attribute__((aligned(16))) list[262144];

typedef struct {
    unsigned int color;
    float x, y, z;
} Vertex;

void rectangle(float x1, float y1, float x2, float y2,
               unsigned int color)
{
    Vertex v[] = {
        {color, x1, y1, 0},
        {color, x2, y1, 0},
        {color, x1, y2, 0},
        {color, x2, y2, 0}
    };

    sceGuDrawArray(GU_TRIANGLE_STRIP,
        GU_COLOR_8888 | GU_VERTEX_32BITF | GU_TRANSFORM_2D,
        4, 0, v);
}

void triangle(float x1, float y1, float x2, float y2,
              float x3, float y3, unsigned int color)
{
    Vertex v[] = {
        {color, x1, y1, 0},
        {color, x2, y2, 0},
        {color, x3, y3, 0}
    };

    sceGuDrawArray(GU_TRIANGLES,
        GU_COLOR_8888 | GU_VERTEX_32BITF | GU_TRANSFORM_2D,
        3, 0, v);
}

int main(void)
{
    sceGuInit();

    sceGuStart(GU_DIRECT, list);

    sceGuDrawBuffer(GU_PSM_8888, (void*)0, BUF);
    sceGuDispBuffer(W, H, (void*)0x88000, BUF);
    sceGuDepthBuffer((void*)0x110000, BUF);

    sceGuOffset(2048 - W / 2, 2048 - H / 2);
    sceGuViewport(2048, 2048, W, H);
    sceGuScissor(0, 0, W, H);

    sceGuEnable(GU_SCISSOR_TEST);
    sceGuDisable(GU_DEPTH_TEST);

    sceGuFinish();
    sceGuSync(0, 0);

    sceDisplayWaitVblankStart();
    sceGuDisplay(GU_TRUE);

    while (1)
    {
        sceGuStart(GU_DIRECT, list);

        sceGuClearColor(GU_RGBA(100, 190, 240, 255));
        sceGuClear(GU_COLOR_BUFFER_BIT);

        // Langit dan pegunungan
        triangle(0, 150, 120, 35, 240, 150,
                 GU_RGBA(65, 105, 90, 255));

        triangle(160, 150, 310, 20, 480, 150,
                 GU_RGBA(75, 120, 95, 255));

        // Rumput
        rectangle(0, 145, 480, 272,
                  GU_RGBA(35, 145, 55, 255));

        // Pepohonan
        triangle(20, 170, 55, 75, 90, 170,
                 GU_RGBA(15, 90, 35, 255));

        triangle(390, 170, 430, 65, 470, 170,
                 GU_RGBA(15, 90, 35, 255));

        // Lintasan menurun
        triangle(190, 75, 290, 75, 450, 272,
                 GU_RGBA(105, 90, 75, 255));

        triangle(190, 75, 450, 272, 30, 272,
                 GU_RGBA(105, 90, 75, 255));

        // Pembatas lintasan
        triangle(180, 75, 190, 75, 30, 272,
                 GU_RGBA(220, 220, 190, 255));

        triangle(290, 75, 300, 75, 450, 272,
                 GU_RGBA(220, 220, 190, 255));

        // Garis tengah lintasan
        rectangle(237, 105, 243, 130,
                  GU_RGBA(255, 255, 255, 255));

        rectangle(225, 155, 255, 185,
                  GU_RGBA(255, 255, 255, 255));

        // Sepeda dan pembalap sederhana
        rectangle(228, 205, 252, 232,
                  GU_RGBA(25, 25, 30, 255));

        rectangle(220, 228, 260, 235,
                  GU_RGBA(230, 35, 35, 255));

        rectangle(230, 235, 250, 265,
                  GU_RGBA(25, 25, 30, 255));

        // Judul
        sceGuFinish();
        sceGuSync(0, 0);

        sceDisplayWaitVblankStart();
        sceGuSwapBuffers();
    }

    sceGuTerm();
    return 0;
}
