#ifndef _IMU_H_
#define _IMU_H_
#define ACCEL_PATH "/sys/class/misc/FreescaleAccelerometer/"
#define MAGNE_PATH "/sys/class/misc/FreescaleMagnetometer/"
#define GYRO_PATH  "/sys/class/misc/FreescaleGyroscope/"
int imuLibInit(void);
void imuLibExit(void);
int imuGetValues(int *ax, int *ay, int *az, int *gx, int *gy, int *gz, int *mx, int *my, int *mz);

int tempLibInit(void);
void tempLibExit(void);
int tempGetValue(float *temp);

#endif
