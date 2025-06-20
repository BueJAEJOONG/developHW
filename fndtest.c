#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>      
#include <sys/ipc.h>     
#include <sys/msg.h>     
#include <linux/input.h> 
#include <sys/msg.h>
#include <pthread.h>
#include <fcntl.h>
#include "fnd.h"

int main()
{
    fndInit();
    for(int i =0; i < 8 ; i++)
    {
        fndDisp(000001,1);
        sleep(1);
        fndDisp(000010,2);
        sleep(1);
        fndDisp(000100,4);
        sleep(1);
        fndDisp(001000,8);
        sleep(1);
        fndDisp(010000,16);
        sleep(1);
        fndDisp(100000,32);
        sleep(1);
    }
    fndExit();
    return 0;

}
