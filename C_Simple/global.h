#pragma once

#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

// 文件包含
#include <stdio.h>
#include <wchar.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include <math.h>
#include "mylib.h"
#include "slist.h"
// 函数原型
/** \brief 根据合适的几率判断是否成功，调用之前，最好使用 srand() 设置种子
 *
 * \param rate胜率，以 MAXRATE 为基准
 *
 * \return 成功返回 true，失败返回 false
 */
bool  AverageProbability(int /*rate*/, int /*MAXRATE*/);


/** \brief 求val的平方根
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
