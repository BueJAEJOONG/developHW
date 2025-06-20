#ifndef _COLORLED_H_
#define _COLORLED_H_

int pwmActiveAll(void);
int pwminactiveAll(void);
int pwmSetDuty(int dutyCycle, int pwmIndex);
int pwmSetPeriod(int Period, int pwmindex);
int pwmSetPercent(int percent, int ledColor);
int pwmStartAll(void);
int pwmLedInit(void);

#endif
