#include <stdio.h>

int main ()
{
    int a = 1000;
    float d = 3.0f / 7;

    int y = 0;
    float yy = 0.0f;

    int i = 0;
    for (i = 0; i < a; ++i) {
        yy += d;
        y = (int) yy;
        printf ("add [(float) 3/7] %5d times, int %d float %f\n", i+1, y, yy);
    }

    return 0;
}
