// The functions contained in this file are pretty dummy
// and are included only as a placeholder. Nevertheless,
// they *will* get included in the static library if you
// don't remove them :)
//
// Obviously, you 'll have to write yourself the super-duper
// functions to include in the resulting library...
// Also, it's not necessary to write every function in this file.
// Feel free to add more files in this project. They will be
// included in the resulting library.
#ifdef __cplusplus
extern "C"
{
#endif


#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"



void* myalloc(size_t cbSize)
{
    void *p = malloc(cbSize);
    if (p==NULL) {
        fprintf(stderr, "failed allocate memory");
        exit(EXIT_FAILURE);
    }
    return p;
}

int average_int(int a, int b)
{
    div_t t1 = div(a,2);
    div_t t2 = div(b,2);
    return t1.quot + t2.quot + (t1.rem + t2.rem) / 2;
}

char *s_gets(char buf[], int bufSize)
{
    char *ret_val = fgets(buf, bufSize, stdin);
    if (ret_val) {
        char *temp;
        if (NULL != (temp = strchr(buf, '\n')))
            *temp = '\0';
        else
            ignore('\n');
    }
    return ret_val;
}

/// quickSort assistant function
static inline void  swapTwoItems(int a[], size_t i, size_t j)
{
//    a[i] ^= a[j];
//    a[j] ^= a[i];
//    a[i] ^= a[j];
    int temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

void  quickSort(int a[], size_t n)
{
    if (n <= 1)
        return;
    if (n == 2) {
        if (a[1] < a[0])
            swapTwoItems(a, 0, 1);
        return;
    }
    // last 为划分两部的枢轴，即a[0]所应在的位置
    // 在 swapTwoItems(a, 0, last) 之前 last 对应的是小于 a[0] 区段的末尾
    size_t last = 0;
    for (size_t i = 1; i < n; ++i) {
        if (a[i] < a[0] && ++last != i)
            swapTwoItems(a, i, last);
    }
    swapTwoItems(a, 0, last);

    quickSort(a, last - 1);
    quickSort(a + last + 1, n - last - 1);
}
#ifdef __cplusplus
}
#endif
