#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
    printf("Hello world!\n");
    char temp[20];
    char upc[12];
    do {
        printf("输入通用产品代码(x-xxxxx-xxxxx-x): ");// 0-24600-01003-0
        fgets(temp, 20, stdin);

        printf("输入的是:%s\n", temp);
        if (temp[1] != '-' 
            || temp[7] != '-' 
            || temp[13] != '-') {
            return EXIT_FAILURE;
        }

        sscanf(temp, "%1s-%5s-%5s-%1s", upc, upc + 1, upc + 6, upc + 11); // %1s%*c%5s%*c%5s%*c%1s

        int sum1 = upc[0] + upc[2] + upc[4] + upc[6] + upc[8] + upc[10] - 6 * '0';
        int sum2 = upc[1] + upc[3] + upc[5] + upc[7] + upc[9] - 5 * '0';

        int result = 9 - (sum1 * 3 + sum2 - 1) % 10;

        printf("%s\n", result == upc[11] - '0' ? "Valid" : "Invalid");

        puts("Do you want go on(y/n)?");
        if (tolower(getchar()) == 'n') {
            break;
        } else {
            while (getchar() != '\n') {
                continue;
            }
        }
    } while (1);
    return 0;
}
