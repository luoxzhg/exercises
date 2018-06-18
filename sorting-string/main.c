#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../mylib/mylib.h"
#define SIZE 81  // string length limit, including null character
#define LIM  20  // maximum number of lines to be read
#define HALT ""  // null string to stop input

/*********************************************
** string-pointer-sorting funciton
** @Purpose:  按增序排序strings
** 使用直接插入排序法
** @Param: strings is a array of char*
** @Param: num is the number of the array
*/
void  strsort(char *strings[], int num);

int  compare(const void* p1, const void* p2)
{
    return strcmp(*(char**)p1, *(char**)p2);
}

int main()
{
    printf("Hello world!\n");
    printf("input up to %d lines, and I will sort them.\n", LIM);
    puts("To stop, press the Enter key at a line's start.");
    char input[LIM][SIZE];
    char *pinput[LIM];
    int cnt = 0;

    while (cnt < LIM
            && s_gets(input[cnt], SIZE) != NULL && *input[cnt] != '\0') {
        pinput[cnt] = input[cnt];
        ++cnt;
    }
    //strsort(pinput, cnt);
    qsort(pinput, cnt, sizeof(char*), compare);
    puts("Here is the sorted list: ");
    for (int i = 0; i < cnt; ++i)
        puts(pinput[i]);

    return 0;
}

void swapstr(char **pstr1, char **pstr2)
{
    char *temp = *pstr1;
    *pstr1 = *pstr2;
    *pstr2 = temp;
}

void strsort(char *strings[], int num)
{
    for (int i = 1; i != num; ++i) {
        for (int j = i; j != 0; --j)
            if (strcmp(strings[j], strings[j-1]) < 0)
                swapstr(&strings[j], &strings[j-1]);
    }
}
