#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>


int gyro_data[3];
static pthread_t gyro_thread_id;
static int end_thread_flag = 0;

void* gyro_thread_func(void* arg)
{
    FILE *fp = NULL;
    while(!end_thread_flag)
    {
        fp = fopen(GYROPATH "data", "rt");
        if (fp == NULL) {
            usleep(100000);
            continue;
        }
        fscanf(fp, "%d, %d, %d", &gyro_data[0], &gyro_data[1], &gyro_data[2]);
        fclose(fp);
        usleep(100000);
    }
    return NULL;
}

int gyroInit(void)
{
    int fd = 0;
    fd = open(GYROPATH "enable", O_WRONLY);
    if (fd < 0) {
        perror("Failed to open gyroscope enable file");
        return 0;
    }
    dprintf(fd, "1");
    close(fd);

    if (pthread_create(&gyro_thread_id, NULL, gyro_thread_func, NULL) != 0)
    {
        perror("gyroscope thread create error");
        return 0;
    }
    return 1;
}

void gyroExit(void)
{
    end_thread_flag = 1; 
    pthread_join(gyro_thread_id, NULL); 

    int fd = open(GYROPATH "enable", O_WRONLY);
    if (fd >= 0) {
        dprintf(fd, "0");
        close(fd);
    }
}
