// include�ļ�
#include <stdio.h>
#include "mylib.h"
#include <string.h>
#include <limits.h>

int a[10];

struct ABC{int x,y;};
/// ����ʵ��

char *mygets(char *dest, int bufSize)
{
    char *temp = dest;
    int  maxSize = bufSize;
    int  ch;
    /// --bufSize ��ʾ��ǰ�����Դ洢���ַ�������������β���ַ�
    while (--bufSize && EOF != (ch = getchar())
            && '\n' != (*dest++ = (char)ch))  // \fixme �Ƿ�洢'\n'
        continue;

    /// �������ȡ�ַ�֮ǰ���� EOF ���ȡ����������error
    if (EOF == ch && (ferror(stdin) || bufSize == maxSize - 1))
        return  NULL;

    *dest = '\0';
    return temp;
}

int myputs(const char *str) { return fputs(str, stdout); }


const char *getbufline(FILE *is, int delim)
{
    /// �°汾�����ε���֮�䲻��Ҫ���·����ڴ�
    static char *str = NULL;
    static size_t size = BUFSIZ;
    if (NULL == str)
        str = New(char, size);

//    /// ʹ���±�
//    size_t cnts = 0;
//    int ch;
//    while (EOF != (ch = getc(is)) && ch != delim)
//    {
//        if (cnts == size-1)   // �ﵽ���һ��λ��, ���·���
//        {
//            if (size >= (size_t)INT_MIN)  // ��� size �ﵽ���ֵ
//            {
//                fputs("String is out of max length!\n", stderr);
//                exit(EXIT_FAILURE);
//            }
//
//            size <<= 1;
//
//            if (NULL == (str = (char *)realloc(str, sizeof(char) * size)))   // ����ط���ʧ��
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

    /// ʹ��ָ��
    char *temp = str;
    int  ch;
    while (EOF != (ch = fgetc(is)) && ch != delim) {
        // ���
        if (temp == str + size - 1) { // �����ǰָ�����һ�����ַ���λ��
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
                /// realloc���ܵ����ڴ����·��䣬��Ҫ���� temp
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
