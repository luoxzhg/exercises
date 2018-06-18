#pragma once

#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

// �ļ�����
#include <stdio.h>
#include <wchar.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include <math.h>
#include "mylib.h"
#include "slist.h"
// ����ԭ��
/** \brief ���ݺ��ʵļ����ж��Ƿ�ɹ�������֮ǰ�����ʹ�� srand() ��������
 *
 * \param rateʤ�ʣ��� MAXRATE Ϊ��׼
 *
 * \return �ɹ����� true��ʧ�ܷ��� false
 */
bool  AverageProbability(int /*rate*/, int /*MAXRATE*/);


/** \brief ��val��ƽ����
 *
 * \param  double val
 * \return double
 *
 */
double  mySqrt(double val);

void*  copy_n_byte(void* dest, const void* src, size_t  n);

bool isleapyear(int /*year*/);

unsigned int   reverse_bits(unsigned int  val);

char* find_first_char_of(char* source, char const* charset);

int  sum_of_ints(int argNum, ...);
#endif // GLOBAL_H_INCLUDED
