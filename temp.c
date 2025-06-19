#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define TEMP_DEVICE_PATH "/sys/class/thermal/thermal_zone0/temp"

int tempGetValue(float *temp)
{
    int fd;
    char buf[20];
    long raw_temp;

    fd = open(TEMP_DEVICE_PATH, O_RDONLY);
    if (fd < 0) {
        perror("Failed to open temperature sensor file");
        return -1;
    }

    ssize_t bytes_read = read(fd, buf, sizeof(buf) - 1);
    if (bytes_read <= 0) {
        perror("Failed to read temperature value");
        close(fd);
        return -1;
    }
    buf[bytes_read] = '\0';

    close(fd);

    raw_temp = atol(buf);
    *temp = (float)raw_temp / 1000.0f;

    return 0;
}

