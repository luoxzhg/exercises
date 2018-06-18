#ifndef MYLIB_H_INCLUDED
#define MYLIB_H_INCLUDED

#include <stdio.h>
#include <stdbool.h>
#include <wctype.h>
#include <float.h>
#include <string.h>
#include <assert.h>


#ifdef __cplusplus
extern "C"
{
#endif  // __cplusplus

#ifndef _countof
#define _countof(array)  ((int)(sizeof array / sizeof array[0]))
#endif // _countof


void* myalloc(size_t cbSize);
#undef New
#define  New(type, num)  ((type*)myalloc(sizeof(type)*(num)))
// 修正 gets
#ifdef BUFSIZ
#  define  gets(s)  fgets(s, BUFSIZ, stdin)
#else
#  define  gets(s, bufsize)  fgets(s, bufsize, stdin)
#endif

/******************************************************************
** 忽略标准输入流中的字节，函数在遇到 EOF 或 delim 之后结束
*******************************************************************/
inline static void ignore(int delim)
{
    int ch;
    while ((ch = getchar()) != EOF && ch != delim)
        continue;
}

int average_int(int a, int b);

/******************************************************************
** 从标准输入流中读取一行文本，buf指向缓冲区，bufSize为缓冲区大小
** 函数在一下情况下结束：
**    （1）在读取 bufSize-1 个字符之前遇到 EOF 或 '\n' 符，则使用
**     空字符结束字符串，并返回buf。不保存换行符。
**    （2）在读取 bufSize-1 个字符之后遇到 EOF 或 '\n' 符，与（1）
**     相似。
**    （3）在读取 bufSize-1 个字符之后没有遇到 EOF 或 '\n'，那么将
**     使用空字符结束字符串，并忽略同一行中遗留的所有字符
*******************************************************************/
char *s_gets(char buf[], int bufSize);

static inline char *getline(char buf[], int bufSize)
{
    return s_gets(buf, bufSize);
}

/*******************************************************************
** 判断给定的年份(year)是否是闰年
*******************************************************************/
inline static bool isLeapYear(int year)
{
    assert(year > 0);
    return (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)) ;
}


/*******************************************************************
*** 最简单的快速排序法
********************************************************************/
void  quickSort(int a[], size_t n);

#ifdef __cplusplus
}
#endif  // __cplusplus


#endif // MYLIB_H_INCLUDED
