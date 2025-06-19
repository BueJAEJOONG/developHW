#include <stdio.h>
#include <unistd.h>
#include "buzzer.h"

int main(void)
{
    printf("Buzzer Test Application\n");

    if (buzzerInit() < 0)
    {
        printf("buzzerInit() failed.\n");
        return -1;
    }

    printf("Playing a single note...\n");

    int note = 3; 
    buzzerPlaySong(note);
    usleep(500000);  

    buzzerStopSong();
    sleep(1);

    buzzerExit();

    return 0;
}

