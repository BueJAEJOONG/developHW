#include <stdio.h>
#include <unistd.h>
#include "textlcd.h"

int main(void)
{
    printf("TextLCD Test\n");

  
    printf("Writingmessage to LCD\n");
    text("Hello", "World");
    sleep(3);

    printf("TextLCD Test Finished.\n");
    return 0;
}
