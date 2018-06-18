#pragma once
#ifndef MYLIB_H_INCLUDED
#define MYLIB_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#ifndef BUFSIZ
#define BUFSIZ   512
#endif
// 使用类似 new 操作符的分配函数，经过返回值检测
#define New(type, count)   ((type*)myalloc__((count) * sizeof(type), __FILE__,\
                                             __LINE__))

static inline void *myalloc__(size_t  size, const char *file, int line)
{
    void *pnew = malloc(size);
    if (NULL == pnew) {
        fprintf(stderr, "in file: %s, line: %d: bad alloc!\n", file, line);
        exit(EXIT_FAILURE);
    }
    return pnew;
}

/** \brief  mygets 读取输入字符并存储在dest指定的缓冲区中。
*** mygets在读取 bufSize - 1 个字符，或读取到换行符 '\n'，再或遇到 EOF 时，
*** 函数结束读取字符。如果是遇到换行符，函数读取并存储换行符。
*** 如果在读取任何字符之前遇到 EOF，则返回NULL，缓冲区未修改。
*** 如果遇到错误，则返回NULL，缓冲区内容未定义。
*** \param  dest 指向缓冲区的指针
*** \param  bufSize 缓冲区大小，包括结尾空字符
*** \return 返回 dest
**/
char *mygets(char *dest, int bufSize);

int myputs(char const *str);

void  ignore(FILE *is, int delim);

/*******************************************************************
***
*** 从输入流 is 中读取以delim字符结尾的字符串，
*** 该函数用于实现安全地向程序中输入字符串，该函数
*** 维护一个字符串缓冲区，其返回值只临时存储读取的字符串，
*** 在下一次输入后，上一个输入将被修改。如果希望保存输入，
*** 必须将其复制下来
***
********************************************************************/
const char *getbufline(FILE *is, int delim);

/////////////////////////////////////////////////////////////////////
/// 按位输出
void  displayBits(unsigned int value);

#endif // MYLIB_H_INCLUDED
