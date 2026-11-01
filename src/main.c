
#include <pspkernel.h>
#include <pspdebug.h>
#include <stdio.h>

PSP_MODULE_INFO("Downhill Prototype", 0, 1, 0);

int main(void)
{
    pspDebugScreenInit();

    printf("DOWNHILL PSP PROTOTYPE\n");
    printf("----------------------\n\n");
    printf("Welcome, Rider!\n");
    printf("Prototype is starting...\n\n");
    printf("Next: Bike and Mountain Track");

    sceKernelSleepThread();

    return 0;
}
