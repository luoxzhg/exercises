#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "functions.h"
#include "../mylib/mylib.h"
bool is_primer(int n)
{
    int i;
    bool isPrimer = true;

    for (i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            isPrimer = false;
            break;
        }
    }
    printf("%d is %s a primer\n",
           n, isPrimer ? "" : "not");
    if (!isPrimer)
        printf("%d %% %d = 0", n, i);

    return isPrimer;
}

void func_6_1(void)
{
    float n = 0, max;
    char str[80], maxStr[80];

    while (true)
    {
        printf("Enter a number:");
        getline(str, 80);
        n = atof(str);
        if ( n <= 0)
        {
            printf("The largers number entered was: %s", maxStr);
            return;
        }

        if ( n > max)
        {
            max = n;
            strcpy(maxStr, str);
        }
    }
}

int func_6_2_greatest_common_divisor(int m, int n)
{
    while ( n != 0)
    {
        int a = m % n;
        m = n;
        n = a;
    }
    return m;
}

int sum_array_int(int a[], int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += a[i];
        a[i]++;
    }
    printf("%p\n", a);
    return sum;
}
