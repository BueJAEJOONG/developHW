#include <stdio.h>
#include <unistd.h>
#include "imu.h"

int main(void)
{
    int ax, ay, az;
    int gx, gy, gz;
    int mx, my, mz;

    if (imuLibInit() < 0) {
        printf("imuLibInit() failed.\n");
        return -1;
    }

    printf("Reading IMU Sensor values\n");

    while (1) {
        if (imuGetValues(&ax, &ay, &az, &gx, &gy, &gz, &mx, &my, &mz) < 0) {
            printf("Failed to read IMU values.\n");
            break;
        }

        printf("Acc(x,y,z): %6d, %6d, %6d, ", ax, ay, az);
        printf("Gyro(x,y,z): %6d, %6d, %6d, ", gx, gy, gz);
        printf("Mag(x,y,z): %6d, %6d, %6d\n", mx, my, mz);
        sleep(1);
    }

    imuLibExit();
    printf("IMU Test Finished.\n");
    return 0;
}
