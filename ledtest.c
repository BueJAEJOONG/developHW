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

    int led = (data >> 0) & 0x01;
    
    ledOnOff(0, led); printf("LED :s\n", led ? "on" : "off");
    
    usleep(1000000);

    ledOnOff(0, 0);

    ledLibExit();

    return 0;
}


