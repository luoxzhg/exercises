#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    printf("Hello world!\n");
    int n, digit = 0;
    printf ("��������һ������ֵ:\n");
    scanf("%d", &n);

    do {
        n /= 10;
        digit++;
    } while (n != 0);

    printf("������� %d λ��", digit);
    return 0;
}
