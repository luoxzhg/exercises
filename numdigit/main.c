#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    printf("Hello world!\n");
    int n, digit = 0;
    printf ("输入任意一个整数值:\n");
    scanf("%d", &n);

    do {
        n /= 10;
        digit++;
    } while (n != 0);

    printf("输入的是 %d 位数", digit);
    return 0;
}
