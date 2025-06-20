#include <stdio.h>
#include <unistd.h>
#include "colorled.h"

int main(void)
{
    printf("Color LED\n");

    if (colorLedLibInit() < 0)
    {
        printf("colorLedLibInit() failed.\n");
        return -1;
    }

    printf("Red\n");
    colorLedSet(100, 0, 0);
    sleep(20);

    printf("Green\n");
    colorLedSet(0, 100, 0);
    sleep(20);

    printf("Blue\n");
    colorLedSet(0, 0, 100);
    sleep(20);
    
    printf("Yellow\n");
    colorLedSet(100, 100, 0);
    sleep(20);

    printf("CYAN\n");
    colorLedSet(0, 100, 100);
    sleep(20);

    printf("MAGENTA\n");
    colorLedSet(100, 0, 100);
    sleep(20);

    printf("White\n");
    colorLedSet(100, 100, 100);
    sleep(20);

    colorLedLibExit();
    printf("Color LED Test Finished.\n");
    return 0;
}
