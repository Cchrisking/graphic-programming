#include <stdio.h>
#include <math.h>
#include <float.h>
int main(void)
{
    float f = 123.45;
    printf("Given the number %.2f\n", f);
    float f3;
    modff(f, &f3);
    int x = f3;
    printf("modf() makes %d\n", x);
}
