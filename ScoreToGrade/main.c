#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <math.h>
#include <complex.h>
#include <errno.h>
void pb(int n)
{
    if (n!=0)
    {
        pb(n/2);
        putchar('O' + n%2);
    }
}
int main(void)
{
    
    printf("Hello world!\n");
    printf("%i", sizeof(L'大'));


#if 0    
    int a[10];
    for (int n = 0; n < 10; ++n)
        a[n] = 0;
    int a[] = {12, a[0], a[1]};
    int score;
    char Grade;
    printf("输入成绩：");
    scanf("%d", &score);
    printf("输入的成绩是：%d\n", score);
    
    if (score > 100 || score < 0)
        return EXIT_FAILURE;
    switch (score / 10)
    {
    case 10:
    case 9:
        Grade = 'A';
        break;
    case 8:
        Grade = 'B';
        break;
    case 7:
        Grade = 'C';
        break;
    case 6:
        Grade = 'D';
        break;
    default:
        Grade = 'E';
        break;
    }
    
    putchar(Grade);
#endif
    return 0;
}
