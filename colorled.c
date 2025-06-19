#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "colorled.h"

#define PWM_BASE_SYS_PATH   "/sys/class/pwm/pwmchip"
#define PWM_FREQUENCY       100000
#define MAX_DUTY_CYCLE      100000

static int sysfs_write(const char *path, const char *value)
{
    int fd = open(path, O_WRONLY);
    if (fd < 0) {
        
        return -1;
    }
    write(fd, value, strlen(value));
    close(fd);
    return 0;
}

static void pwm_export(int pwm_index)
{
    char path[128];
    sprintf(path, "%s%d/export", PWM_BASE_SYS_PATH, pwm_index);
    sysfs_write(path, "0");
}

static void pwm_unexport(int pwm_index)
{
    char path[128];
    sprintf(path, "%s%d/unexport", PWM_BASE_SYS_PATH, pwm_index);
    sysfs_write(path, "0");
}

static void pwm_set_value(int pwm_index, const char* property, int value)
{
    char path[128];
    char buffer[20];
    sprintf(path, "%s%d/pwm0/%s", PWM_BASE_SYS_PATH, pwm_index, property);
    sprintf(buffer, "%d", value);
    sysfs_write(path, buffer);
}

static void pwm_set_enable(int pwm_index, int enable)
{
    char path[128];
    sprintf(path, "%s%d/pwm0/enable", PWM_BASE_SYS_PATH, pwm_index);
    sysfs_write(path, enable ? "1" : "0");
}

int colorLedLibInit(void)
{
    pwm_export(0);
    pwm_export(1);
    pwm_export(2);
    usleep(100000); // 0.1초

    pwm_set_value(0, "period", PWM_FREQUENCY);
    pwm_set_value(1, "period", PWM_FREQUENCY);
    pwm_set_value(2, "period", PWM_FREQUENCY);

    colorLedSet(0, 0, 0);

    pwm_set_enable(0, 1);
    pwm_set_enable(1, 1);
    pwm_set_enable(2, 1);

    return 0;
}

void colorLedLibExit(void)
{
    pwm_set_enable(0, 0);
    pwm_set_enable(1, 0);
    pwm_set_enable(2, 0);

    pwm_unexport(0);
    pwm_unexport(1);
    pwm_unexport(2);
}

int colorLedSet(int red, int green, int blue)
{
    if (red < 0) red = 0;
    if (green < 0) green = 0;
    if (blue < 0) blue = 0;

    int duty_red   = (red > 100) ? MAX_DUTY_CYCLE : (red * MAX_DUTY_CYCLE) / 100;
    int duty_green = (green > 100) ? MAX_DUTY_CYCLE : (green * MAX_DUTY_CYCLE) / 100;
    int duty_blue  = (blue > 100) ? MAX_DUTY_CYCLE : (blue * MAX_DUTY_CYCLE) / 100;

    pwm_set_value(0, "duty_cycle", duty_red);
    pwm_set_value(1, "duty_cycle", duty_green);
    pwm_set_value(2, "duty_cycle", duty_blue);

    return 0;
}
