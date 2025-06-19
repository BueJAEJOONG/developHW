#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include "fnd.h"

#define FND_DRIVER_NAME "/dev/perifnd"

static int fd = -1;

int fndLibInit(void)
{
    if (fd >= 0) {
        return 0;
    }

    fd = open(FND_DRIVER_NAME, O_RDWR);
    if (fd < 0) {
        perror("fnd driver open error");
        return -1;
    }
    return 0;
}

void fndLibExit(void)
{
    if (fd >= 0) {
        stFndWriteForm stWriteData;
        memset(&stWriteData, 0, sizeof(stWriteData));
        write(fd, &stWriteData, sizeof(stWriteData));
        close(fd);
        fd = -1;
    }
}


int fndDisp(int num, int dotflag) {
    int fd, temp, i;
    stFndWriteForm stWriteData;

    for (i = 0; i < MAX_FND_NUM; i++) {
        stWriteData.DataDot[i] = (dotflag & (1 << i)) ? 1 : 0;
        stWriteData.DataValid[i] = 1;
    }

    temp = num % 1000000; stWriteData.DataNumeric[0] = temp / 100000;
    temp = num % 100000;  stWriteData.DataNumeric[1] = temp / 10000;
    temp = num % 10000;   stWriteData.DataNumeric[2] = temp / 1000;
    temp = num % 1000;    stWriteData.DataNumeric[3] = temp / 100;
    temp = num % 100;     stWriteData.DataNumeric[4] = temp / 10;
                          stWriteData.DataNumeric[5] = num % 10;

    fd = open(FND_DRIVER_NAME, O_RDWR);
    if (fd < 0) {
        perror("FND open failed");
        return 0;
    }

    write(fd, &stWriteData, sizeof(stFndWriteForm));
    close(fd);
    return 1;
}

int fnd(int num, char mode) {
    if (mode == MODE_STATIC_DIS) {
        return fndDisp(num, 0b1010);
    }
    else if (mode == MODE_TIME_DIS) {
        time_t t;
        struct tm *tm_info;
        int t_num;

        if (time(&t) == -1) return -1;
        tm_info = localtime(&t);
        t_num = tm_info->tm_hour * 10000 + tm_info->tm_min * 100 + tm_info->tm_sec;
        return fndDisp(t_num, 0b1010);
    }
    else if (mode == MODE_COUNT_DIS) {
        for (int i = 0; i <= num; i++) {
            if (!fndDisp(i, 0)) return 0;
            sleep(1);
        }
        return 1;
    }
    return 0;
}


