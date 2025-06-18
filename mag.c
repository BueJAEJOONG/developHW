#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>

int mag_data[3];
static pthread_t mag_thread_id;
static int end_thread_flag = 0;

void* mag_thread_func(void* arg)
{
    FILE *fp = NULL;
    while(!end_thread_flag)
    {
        fp = fopen(MAGPATH "data", "rt");
        if (fp == NULL) {
            usleep(100000);
            continue;
        }
        fscanf(fp, "%d, %d, %d", &mag_data[0], &mag_data[1], &mag_data[2]);
        fclose(fp);
        usleep(100000); 
    }
    return NULL;
}

int magInit(void)
{
    int fd = 0;
    fd = open(MAGPATH "enable", O_WRONLY);
    if (fd < 0) {
        perror("Failed to open magnetometer enable file");
        return 0;
    }
    dprintf(fd, "1");
    close(fd);

    if (pthread_create(&mag_thread_id, NULL, mag_thread_func, NULL) != 0)
    {
        perror("magnetometer thread create error");
        return 0;
    }
    return 1;
}

void magExit(void)
{
    end_thread_flag = 1; 
    pthread_join(mag_thread_id, NULL); 
    int fd = open(MAGPATH "enable", O_WRONLY);
    if (fd >= 0) {
        dprintf(fd, "0");
        close(fd);
    }
}
