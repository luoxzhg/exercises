#include <stdio.h>
#include <stdlib.h>

#define SQUARES  64
#define CROP     1.0E15

int main(void)
{
    printf("Hello world!\n");
    
    printf("square    grains added    total grains    fraction of US total\n");
    
    double current = 1.0, total = 0.0;
    
    for (int cnt = 1; cnt <= SQUARES; ++cnt)
    {
        total += current;
        printf("%4d %15.2e %15.2e %15.2e\n", cnt, current, total, total / CROP);
        current *= 2;
    }
    
    return 0;
}
