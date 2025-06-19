#include <stdio.h>
#include <unistd.h>
#include "imu.h"

int main() {
    float temperature;

    
    if (tempGetValue(&temperature) == 0) {
        printf("now temperature: %.2f °C\n", temperature);
    } else {
        fprintf(stderr, "temperature fail\n");
        return 1; 
    }

    return 0; 
}

