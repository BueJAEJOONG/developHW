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

	
	int msgID = msgget (MESSAGE_ID, IPC_CREAT|0666);

	if (msgID == -1){
		printf ("Cannot get msgQueueID, Return!\r\n");
		return -1;
	}

	buttonInit(); 

	while(1){
		int returnValue = 0;
		returnValue = msgrcv(msgID, &B, sizeof(BUTTON_MSG_T) - sizeof(long int), 0, 0);

		switch(B.keyInput)
		{
			case KEY_HOME:
				printf("HOME");
				break;
			case KEY_BACK:
				printf("BACK");
				break;
			case KEY_SEARCH:
				printf("SEARCH"); 
				break;
			case KEY_MENU:
				printf("MENU"); 
				break;
			case KEY_VOLUMEUP:
				printf("VOLUMEUP");
				break;
			case KEY_VOLUMEDOWN:
				printf("VOLUMEDOWN");
				break;
		}

		
		if ( B.pressed ) {
			printf("pressed\n");
		} else {
			printf("released\n");
		}
	}

	buttonExit(); // 버튼 드라이버 종료
	return 0;
}

