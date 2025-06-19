#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "imu.h"

static void write_enable(const char* path, const char* value)
{
    int fd = open(path, O_WRONLY);
    if (fd < 0) return;
    write(fd, value, strlen(value));
    close(fd);
}

int imuLibInit(void)
{
    write_enable(ACCEL_PATH "enable", "1");
    write_enable(MAGNE_PATH "enable", "1");
    write_enable(GYRO_PATH  "enable", "1");
    return 0;
}

void imuLibExit(void)
{
    write_enable(ACCEL_PATH "enable", "0");
    write_enable(MAGNE_PATH "enable", "0");
    write_enable(GYRO_PATH  "enable", "0");
}

int imuGetValues(int *ax, int *ay, int *az, int *gx, int *gy, int *gz, int *mx, int *my, int *mz)
{
    FILE *fp;
    char path[256];

    sprintf(path, "%s%s", ACCEL_PATH, "data");
    fp = fopen(path, "r");
    if (!fp) return -1;
    fscanf(fp, "%d, %d, %d", ax, ay, az);
    fclose(fp);

    sprintf(path, "%s%s", GYRO_PATH, "data");
    fp = fopen(path, "r");
    if (!fp) return -1;
    fscanf(fp, "%d, %d, %d", gx, gy, gz);
    fclose(fp);
    
    sprintf(path, "%s%s", MAGNE_PATH, "data");
    fp = fopen(path, "r");
    if (!fp) return -1;
    fscanf(fp, "%d, %d, %d", mx, my, mz);
    fclose(fp);

    return 0;
}
