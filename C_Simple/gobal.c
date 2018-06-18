// include�ļ�
#include "global.h"
#include <stdarg.h>
#include <errno.h>


struct ABC{int x,y;};




//-----------------------------------------
// ����ԭ������
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

// ����ƽ����
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

    /// ����һ��ѭ���˳�ʱ��cnts Ҫô���� 1+n��ҪôС�� 1+n
    /// ����1+nʱ���Ѿ�������n���ֽڣ���С��1+nʱ��
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
        // �Ѿɵ�answer����һλ��Ϊ��һ��λ�����ռ�
        // ���val��ǰ��λֵΪ 1���� answer �ĵ�һλ����Ϊ 1
        // Ȼ�󣬽� val ��ֵ����һλ��׼��������һ��λ��ֵ
        answer <<= 1;
        if (val & 1)
            answer |= 1;
        val >>= 1;
    }
//    const  unsigned  MAXSIZE = sizeof(unsigned) * CHAR_BIT;
//    for (unsigned i = 0; i != (MAXSIZE) / 2; ++i)
//    {
//        unsigned  mask1 = val & (0x01u << i);                   // ȡ�ø�λ��ֵ
//        unsigned  mask2 = val & (0x01u << (MAXSIZE - 1u - i));   // ȡ�����λ��ֵ
//
//        // ����Щλ��ֵ���㣬׼������ֵ
//        val &= ~mask1;
//        val &= ~mask2;
//
//        // ������ЩΪ��ֵ
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
        sum += va_arg(arg_ptr, int);   // ��ȡ����
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
