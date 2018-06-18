#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../mylib/mylib.h"


// validate that input is an integer
long  get_long(void);

// validate that the range limits are valid
bool  bad_limits(long begin, long end, long low, long high);

// calculate the sum of the squares of the integers a through b, exclude b
long  sum_squares(long a, long b);


int main()
{
    printf("Hello world!\n");
    const long MIN = -10000;
    const long MAX = 10000;

    printf("This program computes the sum of the squares of"
           " integers in range.\n");
    printf("The lower bound should not be less than %ld, and\n"
           "the upper bound should not be greater than %ld.\n", MIN, MAX);

    do {
        printf("Enter the limits(enter 0 to both limits to quit):\n");
        printf("lower bound: ");
        long start = get_long();
        printf("upper bound: ");
        long end = get_long();

        if (start == 0 && end == 0)
            break;

        if (bad_limits(start, end, MIN, MAX)) {
            printf("please try again!\n");
            continue;
        }
        else {
            printf("The sum of squares of the range %ld to %ld is: %ld.\n",
                   start, end, sum_squares(start, end));
        }
    } while (true);

    printf("Done!\n");

    return 0;
}

long  get_long(void)
{
    long input;
    int  check;
    do {
        check = scanf("%ld", &input);
        ignore('\n');
        if (check != 1)
            printf("your input is not a integer. please try again.\n");
        else
            break;
    } while (true);
//    while (scanf("%ld", &input) != 1) {
//        ignore('\n');
//        printf("your input is not a integer. please try again.\n");
//    }
//    ignore('\n');
    return input;
}

bool  bad_limits(long begin, long end, long low, long high)
{
    bool  retvalue = true;
    if (begin < end && (begin >= low && end <= high))
        retvalue = false;
    return retvalue;
}

long  sum_squares(long a, long b)
{
    long sum = 0;
    for (; a < b; ++a)
        sum += a * a;
    return sum;
}
