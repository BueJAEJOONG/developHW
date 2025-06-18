#ifndef _MAG_H_
#define _MAG_H_

#define MAGNEPATH "/sys/class/misc/FreesclaeMagnetometer/"

#include <pthread.h>

extern int mag_data[3];

int magInit(void);
void magExit(void);

#endif


