#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../mylib/mylib.h"

int comp_string(const void *p, const void *q)
{
    // p, q 的值是字符指针的地址，字符指针指向字符串
    // 我们需要传递的是字符串的地址，即字符指针的值
    // 因此需要先转换到原本类型，然后解引用
    return stricmp(*(const char * const *)p, *(const char * const *)q);
}

int main(void)
{
    printf("Hello world!\n");
    const char *str[] = {   "dfsjieljoji2ej3r44",
                            "dser233r4",
                            "ioejfk",
                            "agdfi",
                            "bdsfjd",
                            "ghdios",
                            "godsoecjis",
                            "ersfdsdfs",
                            "adfde",
                            "Bdef",
                            "Cde",
                            "ger"
                        };
    size_t cnts =  sizeof(str) / sizeof(*str);
    qsort(str, cnts, sizeof(*str), comp_string);

    for (size_t i = 0; i < cnts; ++i)
    {
        puts(str[i]);
    }
    return 0;
}
