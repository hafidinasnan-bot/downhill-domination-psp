
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspdisplay.h>

PSP_MODULE_INFO("Downhill Prototype", 0, 1, 0);

int main(void)
{
    pspDebugScreenInit();

    pspDebugScreenSetTextColor(0xFFFFFFFF);

    pspDebugScreenPrintf("DOWNHILL PSP PROTOTYPE\n");
    pspDebugScreenPrintf("----------------------\n\n");

    pspDebugScreenPrintf("Welcome, Rider!\n\n");
    pspDebugScreenPrintf("PSP application is running!\n\n");
    pspDebugScreenPrintf("Next: Bike and Mountain Track\n");

    while (1)
    {
        sceDisplayWaitVblankStart();
    }

    return 0;
}
