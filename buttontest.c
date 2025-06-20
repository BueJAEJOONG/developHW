#include <stdio.h>
#include <sys/msg.h>
#include <unistd.h>
#include "button.h"

#define KEY_BACK 158 

int main(void)
{
    printf("Button Test Application\n");
    
    int msgID;
    BUTTON_MSG_T receivedMsg;
    msgID = buttonInit();
    if (msgID < 0)
    {
        printf("buttonInit() failed.\n");
        return -1;
    }

    printf("Waiting for button press... (Press BACK button to exit)\n");

    while(1)
    {
        msgrcv(msgID, &receivedMsg, sizeof(receivedMsg) - sizeof(long int), 0, 0);
        
        printf("Button Pressed: Key Code %d\n", receivedMsg.keyInput);

        if (receivedMsg.keyInput == KEY_BACK)
        {
            printf("BACK button pressed. Exiting.\n");
            break;
        }
    }
    
    buttonExit();

    return 0;
}
