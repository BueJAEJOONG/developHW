#ifndef _ACCEL_H_
#define _ACCEL_H_

#define ACCELPATH "/sys/class/misc/FreescaleAccelerometer/"

extern int g_accel_dat[3];

int accelInit(void);
void accelExit(void);

#endif

