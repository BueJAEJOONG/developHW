#include <stdio.h>
#include <unistd.h>
#include "colorled.h"

int main(void)
{
    printf("Color LED Test Application\n");

    if (colorLedLibInit() < 0)
    {
        printf("colorLedLibInit() failed.\n");
        return -1;
    }

    printf("Red\n");
    colorLedSet(100, 0, 0);
    sleep(2);

    printf("Green\n");
    colorLedSet(0, 100, 0);
    sleep(2);

    printf("Blue\n");
    colorLedSet(0, 0, 100);
    sleep(2);
    
    printf("Yellow\n");
    colorLedSet(100, 100, 0);
    sleep(2);

    printf("White\n");
    colorLedSet(100, 100, 100);
    sleep(2);

    colorLedLibExit();
    printf("Color LED Test Finished.\n");
    return 0;
}
