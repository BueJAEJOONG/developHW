#include <stdio.h>
#include <unistd.h>
#include "fnd.h"

int main(void)
{
    printf("FND Test\n");

    if (fndLibInit() < 0)
    {
        printf("fndLibInit() failed.\n");
        return -1;
    }
	for (int n = 0; n<5; n++)
    {   
	int value = n*111111; 
        printf("Displaying: %d\n", value);
        fndDisp(value, 0); 
        sleep(1);
    }
    
	fndDisp(0, 0b001010); //dot
    printf("Displaying dots...\n");
    sleep(1);


    fndLibExit();
    printf("FND Test Finished.\n");
    return 0;
}
