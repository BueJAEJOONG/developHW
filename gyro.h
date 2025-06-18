#ifndef _GYRO_H_
#define _GYRO_H_

#define GYROPATH "/sys/class/misc/FreescaleGyroscope/"

#include <pthread.h>

extern int gyro_data[3];

int gyroinit(void);
void gyroExit(void);

#endif

