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
// ���� gets
#ifdef BUFSIZ
#  define  gets(s)  fgets(s, BUFSIZ, stdin)
#else
#  define  gets(s, bufsize)  fgets(s, bufsize, stdin)
#endif

/******************************************************************
** ���Ա�׼�������е��ֽڣ����������� EOF �� delim ֮�����
*******************************************************************/
inline static void ignore(int delim)
{
    int ch;
    while ((ch = getchar()) != EOF && ch != delim)
        continue;
}

int average_int(int a, int b);

/******************************************************************
** �ӱ�׼�������ж�ȡһ���ı���bufָ�򻺳�����bufSizeΪ��������С
** ������һ������½�����
**    ��1���ڶ�ȡ bufSize-1 ���ַ�֮ǰ���� EOF �� '\n' ������ʹ��
**     ���ַ������ַ�����������buf�������滻�з���
**    ��2���ڶ�ȡ bufSize-1 ���ַ�֮������ EOF �� '\n' �����루1��
**     ���ơ�
**    ��3���ڶ�ȡ bufSize-1 ���ַ�֮��û������ EOF �� '\n'����ô��
**     ʹ�ÿ��ַ������ַ�����������ͬһ���������������ַ�
*******************************************************************/
char *s_gets(char buf[], int bufSize);

static inline char *getline(char buf[], int bufSize)
{
    return s_gets(buf, bufSize);
}

/*******************************************************************
** �жϸ��������(year)�Ƿ�������
*******************************************************************/
inline static bool isLeapYear(int year)
{
    assert(year > 0);
    return (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)) ;
}


/*******************************************************************
*** ��򵥵Ŀ�������
********************************************************************/
void  quickSort(int a[], size_t n);

#ifdef __cplusplus
}
#endif  // __cplusplus


#endif // MYLIB_H_INCLUDED
