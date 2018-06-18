// include文件
#include "global.h"
#include <stdarg.h>
#include <errno.h>


struct ABC{int x,y;};




//-----------------------------------------
// 函数原型声明
// ----------------------------------------

bool  AverageProbability(int rate, int MAXRATE)
{
    int  temp = 0;
    do
    {
        temp = rand();
    }
    while (temp >= RAND_MAX / MAXRATE * MAXRATE);

    return  rate > temp % MAXRATE;
}
///////////////////////////////////////////////////////////////

// 计算平方根
static  inline double  nextvalued(double val, double a1)
{
    return  (a1 + val / a1) / 2;
}
double  mySqrt(double val)
{

    double  a1 = 1.0;
    double  an = nextvalued(val, a1);
    const  double  EPSILON = 1e-10;
    while (fabs(an - a1) > EPSILON)
    {
        a1 = an;
        an = nextvalued(val, a1);
    }

    return a1;
}

////////////////////////////////////////////////////////////////////



void*  copy_n_byte(void* dest, const void* src, size_t  n)
{
    char* dest1 = (char*)dest;
    const char* src1 = (const char*) src;
    size_t  cnts = 0;
    while (cnts++ != n && '\0' != (*dest1++ = *src1++))
        continue;
//    for (; cnts != n; ++cnts)
//    {
//        if ('\0' == (*dest1++ = *src1++))
//        {
//            ++cnts;
//            break;
//        }
//    }

    /// 从上一个循环退出时，cnts 要么等于 1+n，要么小于 1+n
    /// 等于1+n时，已经复制了n个字节；当小于1+n时，
    --cnts;
    while (cnts++ != n)
    {
        *dest1++ = '\0';
    }

    return dest;
}

bool isleapyear(int year)
{
    if (year % 4 != 0)
        return  false;
    else
        return  !(year % 100 == 0 && year % 400 != 0);
}
//////////////////////////////////////////////////////////////////////////


unsigned int   reverse_bits(unsigned int  val)
{
    unsigned answer = 0;
    for (unsigned i = 1; i != 0; i <<= 1)
    {
        // 把旧的answer左移一位，为下一个位留出空间
        // 如果val当前的位值为 1，则将 answer 的第一位设置为 1
        // 然后，将 val 的值右移一位，准备测试下一个位的值
        answer <<= 1;
        if (val & 1)
            answer |= 1;
        val >>= 1;
    }
//    const  unsigned  MAXSIZE = sizeof(unsigned) * CHAR_BIT;
//    for (unsigned i = 0; i != (MAXSIZE) / 2; ++i)
//    {
//        unsigned  mask1 = val & (0x01u << i);                   // 取得该位的值
//        unsigned  mask2 = val & (0x01u << (MAXSIZE - 1u - i));   // 取得相对位的值
//
//        // 将这些位的值清零，准备交换值
//        val &= ~mask1;
//        val &= ~mask2;
//
//        // 设置这些为的值
//        val |= mask1 << (MAXSIZE - 1u - 2u * i);
//        val |= mask2 >> (MAXSIZE - 1u - 2u * i);
//    }
    return  val;
}
//////////////////////////////////////////////////////////////////////////

char* find_first_char_of(char* source, char const* charset)
{
    char* temp = source;
    while (*temp != '\0')
    {
        if (NULL != strchr(charset, *temp))
            return (char*)temp;
        else
            ++temp;
    }
    return NULL;
}

int  sum_of_ints(int argNum, ...)
{
    if (argNum <= 0)
    {
        fprintf(stderr, "in function sum_of_ints error arguments");
        abort();
    }
    va_list  arg_ptr;   // declare an argument list pointer
    va_start(arg_ptr, argNum);

    int sum = 0;
    for (int i = 0; i != argNum; ++i)
        sum += va_arg(arg_ptr, int);   // 获取参数
    va_end(arg_ptr);

    return sum;
}

//void  print_redger(int value)
//{
//#ifdef  OPTION_LONG
//    print_redger_long(value);
//#elifdef OPTION_DETAILED
//    print_dedger_detailed(value);
//#else
//    //print_redger_default(value);
//#endif // OPTION_LONG
//}
