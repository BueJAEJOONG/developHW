#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "led.h"

int main(int argc, char **argv)
{
    unsigned int data;

    printf("LED Test Application\n");

    if (argc < 2)
    {
        printf("Usage: %s <hex byte>\n", argv[0]);
        printf("Example:\n");
        printf("  %s 0x05 ; LED 1 and 4 ON\n", argv[0]);
        printf("  %s 0xff ; All LEDs ON\n", argv[0]);
        printf("  %s 0x00 ; All LEDs OFF\n", argv[0]);
        return -1;
    }

    data = strtol(argv[1], NULL, 16);
    if (ledLibInit() < 0)
    {
        printf("ledLibInit() failed.\n");
        return -1;
    }

    for (int i = 0; i < 8; i++)
    {
        int on = (data >> i) & 0x01;
        ledOnOff(i, on);            
        printf("LED %d: %s\n", i + 1, on ? "ON" : "OFF");
    }

    usleep(1000000);
    printf("Turning all LEDs OFF...\n");
    for (int i = 0; i < 8; i++)
    {
        ledOnOff(i, 0);
    }

    ledLibExit();

    return 0;
}


