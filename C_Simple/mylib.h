#pragma once
#ifndef MYLIB_H_INCLUDED
#define MYLIB_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#ifndef BUFSIZ
#define BUFSIZ   512
#endif
// ʹ������ new �������ķ��亯������������ֵ���
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

/** \brief  mygets ��ȡ�����ַ����洢��destָ���Ļ������С�
*** mygets�ڶ�ȡ bufSize - 1 ���ַ������ȡ�����з� '\n'���ٻ����� EOF ʱ��
*** ����������ȡ�ַ���������������з���������ȡ���洢���з���
*** ����ڶ�ȡ�κ��ַ�֮ǰ���� EOF���򷵻�NULL��������δ�޸ġ�
*** ������������򷵻�NULL������������δ���塣
*** \param  dest ָ�򻺳�����ָ��
*** \param  bufSize ��������С��������β���ַ�
*** \return ���� dest
**/
char *mygets(char *dest, int bufSize);

int myputs(char const *str);

void  ignore(FILE *is, int delim);

/*******************************************************************
***
*** �������� is �ж�ȡ��delim�ַ���β���ַ�����
*** �ú�������ʵ�ְ�ȫ��������������ַ������ú���
*** ά��һ���ַ������������䷵��ֵֻ��ʱ�洢��ȡ���ַ�����
*** ����һ���������һ�����뽫���޸ġ����ϣ���������룬
*** ���뽫�临������
***
********************************************************************/
const char *getbufline(FILE *is, int delim);

/////////////////////////////////////////////////////////////////////
/// ��λ���
void  displayBits(unsigned int value);

#endif // MYLIB_H_INCLUDED
