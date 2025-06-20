#include <stdio.h>
#include <unistd.h>
#include "buzzer.h"

const int melody[] = {1, 2, 3, 4, 5, 6, 7, 8};

int main(void)
{
    printf("Buzzer Test Application\n");

    if (buzzerInit() < 0)
    {
        printf("buzzerInit() failed.\n");
        return -1;
    }

    printf("Playing a simple melody...\n");

    int noteCount = sizeof(melody) / sizeof(melody[0]);
    for (int i = 0; i < noteCount; i++)
    {
        printf("Playing note: %d\n", melody[i]);
        buzzerPlaySong(melody[i]);
        usleep(300000); 
    }

    printf("Melody finished.\n");


    buzzerStopSong();
    sleep(1); 

    buzzerExit();

    return 0;
}
