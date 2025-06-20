#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "colorled.h"

void colorLedSet(int r_percent, int g_percent, int b_percent) {
    printf("Setting RGB: R=%d%%, G=%d%%, B=%d%%\n", r_percent, g_percent, b_percent);
    pwmSetPercent(r_percent, PWM_COLOR_R);
    pwmSetPercent(g_percent, PWM_COLOR_G);
    pwmSetPercent(b_percent, PWM_COLOR_B);
}

typedef struct {
    int r;
    int g;
    int b;
    const char* name;
} Color;

int main(int argc, char **argv)
{
    printf("Color LED Test Program\n");

    if (pwmLedInit() < 0)
    {
        printf("pwmLedInit() failed. Check device paths and permissions.\n");
        pwminactiveAll();
        return -1;
    }
    printf("PWM LED initialized successfully.\n");

    if (argc == 4) {
        printf("Setting LED to R:%s G:%s B:%s based on arguments.\n", argv[1], argv[2], argv[3]);
        colorLedSet(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
        sleep(5);
        printf("Turning off LED and exiting.\n");
        colorLedSet(0, 0, 0);
        pwminactiveAll();
        return 0;
    } else if (argc != 1) {
        printf("Usage: %s [R_percent] [G_percent] [B_percent]\r\n", argv[0]);
        printf("ex) %s 100 100 100 ==> full white color\r\n", argv[0]);
        printf("Running default color sequence test...\n");
    }

    Color colors[] = {
        {100, 0, 0, "Red (100% R)"},
        {0, 100, 0, "Green (100% G)"},
        {0, 0, 100, "Blue (100% B)"},
        {100, 100, 0, "Yellow (100% R, 100% G)"},
        {0, 100, 100, "Cyan (100% G, 100% B)"},
        {100, 0, 100, "Magenta (100% R, 100% B)"},
        {100, 100, 100, "White (100% R, G, B)"},
        {50, 0, 50, "Purple (50% R, 50% B)"},
        {100, 50, 0, "Orange (100% R, 50% G)"},
        {0, 0, 0, "Off (0% R, G, B)"},
        {30, 30, 30, "Dim White (30% R, G, B)"}
    };

    int numColors = sizeof(colors) / sizeof(colors[0]);
    int display_duration_sec = 2;

    printf("\n--- Starting Color Sequence Test ---\n");
    for (int i = 0; i < numColors; i++) {
        printf("Displaying: %s\n", colors[i].name);
        colorLedSet(colors[i].r, colors[i].g, colors[i].b);
        sleep(display_duration_sec);
    }
    printf("--- Color Sequence Test Finished ---\n\n");

    printf("Turning off LED...\n");
    colorLedSet(0, 0, 0);
    sleep(1);

    pwminactiveAll();
    printf("Color LED Test Finished. Resources unexported.\n");
    return 0;
}
