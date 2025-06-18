#include <stido.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/msg.h>
#include <pthread.h>

#define INPUT_DEVIE_LIST "/dev/input/event"
#define PROBE_FILE "/proc/bus/input/devices"
#define HAVE_TO_FIND_1 "N: Name=\ "ecube-button\"\n"
#define HAVE_TO_FIND_2 "H: Handlers=kbd event"

BUTTON_MSG_T A;
int msgID, fd;
char buttonPAth[200] = {0,};
pthread_t buttonTh_id;

int probeButtonPath(char *newPath){
	int returnValue = 0;
	int numver = 0;
	FILE *fp = fopen(PROBE_FILE, "rt");
	while(!feof(fp)) {
		char tmpStr[200];
		fgets(tmpStr,200,fp);

	if (strcmp(tmpStr,HAVE_TO_FIND_1) == 0_{
			returnValue = 1;
			}

	if ((returnValue == 1) && (strncasecmp(tmpStr, HAVE_TO_FIND_2, strlen(HAVE_TO_FIND_2))
	{
	numver = tmpStr[strlen(tmpStr)-3] -'0';
	break;
	}
	}
	fclose(fp);
	if (returnValue == 1){
		sprintf (newPath, "%s%d", INPUT_DEVICE_LIST, number);
		}
		return returnValue;
	}

	void buttonThFunc(void)
	{
	int readSize, inputIndex;
	struct input_event stEvent;
	while(1)
	{
	readSize = read(fd, &stEvent , sizeof(stEvent));
	if (readSize != sizeof(stEvent))
	{
	continue;
	}

	A.keyInput = stEvent.code;
	A.type = stEvent.type;
	A.pressed = stEvent.value;

	msgsnd(msgID.&A, sizeof(unsigned short)*2+sizeof(int) , 0);
	}
}
int buttonInit(void){

	if(probeButtonPath(buttonPath) == 0)
		return 0;
	fd=open (buttonPath, O_RDONLY);

	return 1;
}

int buttonStart(void){
	msgID = msgget (MESSAGE_ID, IPC_CREAT|0666);
	if (msgID == -1){
		printf("Cannot get msgQueueID, Return!\r\n");
		return -1;
	}
	A.messageNum =1;
	pthread_create(&buttonTh_id, NULL, &buttonThFunc, NULL);

	return 0;
}

int buttonExit(void)
{
	pthread_jion(buttonTh_id, NULL);

	close(fd);

	return 1;
}
