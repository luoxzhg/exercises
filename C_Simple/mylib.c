// include文件
#include <stdio.h>
#include "mylib.h"
#include <string.h>
#include <limits.h>

int a[10];

struct ABC{int x,y;};
/// 函数实现

char *mygets(char *dest, int bufSize)
{
    char *temp = dest;
    int  maxSize = bufSize;
    int  ch;
    /// --bufSize 表示当前还可以存储的字符数，不包括结尾空字符
    while (--bufSize && EOF != (ch = getchar())
            && '\n' != (*dest++ = (char)ch))  // \fixme 是否存储'\n'
        continue;

    /// 如果在提取字符之前遇到 EOF 或读取过程中遇到error
    if (EOF == ch && (ferror(stdin) || bufSize == maxSize - 1))
        return  NULL;

    *dest = '\0';
    return temp;
}

int myputs(const char *str) { return fputs(str, stdout); }


const char *getbufline(FILE *is, int delim)
{
    /// 新版本，两次调用之间不需要重新分配内存
    static char *str = NULL;
    static size_t size = BUFSIZ;
    if (NULL == str)
        str = New(char, size);

//    /// 使用下标
//    size_t cnts = 0;
//    int ch;
//    while (EOF != (ch = getc(is)) && ch != delim)
//    {
//        if (cnts == size-1)   // 达到最后一个位置, 重新分配
//        {
//            if (size >= (size_t)INT_MIN)  // 如果 size 达到最大值
//            {
//                fputs("String is out of max length!\n", stderr);
//                exit(EXIT_FAILURE);
//            }
//
//            size <<= 1;
//
//            if (NULL == (str = (char *)realloc(str, sizeof(char) * size)))   // 如果重分配失败
//            {
//                fputs("Bad alloc!\n", stderr);
//                exit(EXIT_FAILURE);
//            }
//        }
//
//        str[cnts++] = (char)ch;
//    }
//
//    str[cnts] = '\0';

    /// 使用指针
    char *temp = str;
    int  ch;
    while (EOF != (ch = fgetc(is)) && ch != delim) {
        // 检测
        if (temp == str + size - 1) { // 如果当前指向最后一个空字符的位置
            if (size >= (size_t)INT_MIN) {
                fputs("String is out of max length!\n", stderr);
                exit(EXIT_FAILURE);
            }

            size <<= 1;

            char *str1 = (char *)realloc(str, sizeof(char) * size);
            if (NULL == str1) {
                fputs("Bad alloc!\n", stderr);
                exit(EXIT_FAILURE);
            } else if (str1 != str) {
                /// realloc可能导致内存重新分配，需要更新 temp
                temp = str1 + (str - temp);
                str = str1;
            }
        } // end if
        *temp++ = (char)ch;
    } // end while
    *temp = '\0';
    return str;
}

void  ignore(FILE *is, int delim)
{
    while (getc(is) != delim)
        continue;
}

void  displayBits(unsigned int value)
{
    const unsigned  SHIFT = CHAR_BIT * sizeof(unsigned int) - 1;
    const unsigned  MASK = 1u << SHIFT;

    for (unsigned i = 0; i <= SHIFT; ++i) {
        putchar((value << i) & MASK ? '1' : '0');
        if ((i + 1) % CHAR_BIT == 0)
            putchar(' ');
    }
    putchar('\n');
}
