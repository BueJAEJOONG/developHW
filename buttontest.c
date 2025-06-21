#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/msg.h>
#include <pthread.h>
#include "button.h"

int main(int argc, char *argv[])
{
    BUTTON_MSG_T B;

    int msgID = buttonInit();
    if (msgID < 0)
    {
        printf("buttonInit() failed. Cannot get msgQueueID, Return!\r\n");
        return -1;
    }

    printf("Waiting for button press events...\n");

    while(1)
    {
        int returnValue = 0;
        returnValue = msgrcv(msgID, &B, sizeof(BUTTON_MSG_T) - sizeof(long int), 0, 0);

        if (returnValue < 0) {
            perror("msgrcv failed");
            break;
        }

        switch(B.keyInput)
        {
            case KEY_HOME:
                printf("HOME ");
                break;
            case KEY_BACK:
                printf("BACK ");
                break;
            case KEY_SEARCH:
                printf("SEARCH ");
                break;
            case KEY_MENU:
                printf("MENU ");
                break;
            case KEY_VOLUMEUP:
                printf("VOLUMEUP ");
                break;
            case KEY_VOLUMEDOWN:
                printf("VOLUMEDOWN ");
                break;
            default:
                printf("UNKNOWN_KEY (%d) ", B.keyInput);
                break;
        }


        if ( B.pressed ) {
            printf("pressed\n");
        } else {
            printf("released\n");
        }
    }

    buttonExit();
    return 0;
}


