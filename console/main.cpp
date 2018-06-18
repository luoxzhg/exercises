// include files
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "myString.h"
#include <windows.h>
#include <w32api.h>
// using declarations
using std::endl;
using std::cout;
using std::cin;

//union POINT
//{
//    uint32_t                         value;
//#ifdef __BIG_ENDIAN__
//    struct{uint16_t y; uint16_t x;}  point;
//#else
//    struct{uint16_t x; uint16_t y;}  point;
//#endif // __BIG_ENDIAN__
//};

// function prototype
char* CommonSubString(const char* str1, const char* str2);

bool IsBigendian();

int  cnt5(int val);

char* myitoa(char* buf, long num, bool low = true);

inline void print(void)
{
    cout << "HI this is function print\n";
}
/// main function
int main(void)
{
    cout << "Hello world!" << endl;
    cout << std::hex << std::showbase << WINVER << endl;
//    cout << test3(0xff) << endl;
//    cout << sizeof (long long) << endl;
//    char s[]  = {"1233dedfs"};
//    cout << s << endl;
//    cout << -3 / 2 << " " << -3 % 2 << endl;
//    const char* str1 = "abdefihikh";
//    const char* str2 = "abcdfgiimh";
//    char* sub = CommonSubString(str1, str2);  /// sub 是动态内存需要释放
//    cout << sub << endl;
//    free(sub);

    return 0;
}


// implementations

char* myitoa(char* str, long num, bool low)
{
    assert(str != NULL);
    str[0] = '0';
    str[1] = 'x';
    str[10] = '\0';

    for (int i = 9; i != 1; --i)
    {
        str[i] = num & 0xf;
        num >>= 4;

        if (str[i] >= 0 && str[i] < 10)
            str[i] += '0';
        else
            str[i] += (low ? 'a' - 10 : 'A' - 10);   // 'a'使用小写字母，'A'使用大写字母
    }

//    for (int i = 33; i != 1; --i)
//    {
//        str[i] = (num & 0x01) + '0';
//        num >>= 1;
//    }
    return str;
}

int  cnt5(int val)
{

    int  cnt = 0; while (val % 5 == 0)
    {
        ++cnt;
        val /= 5;
    }

    return cnt;
}


bool IsBigendian(void)
{
    union { short  a; char   b; } temp = { 0x0100 };
    return  temp.b;
}

char* CommonSubString(const char* str1, const char* str2)
{
    assert(str1 && str2);
    int len1 = strlen(str1);
    int len2 = strlen(str2);

    if (len1 < len2)
        return CommonSubString(str2, str1);

    char* substring = new char[len2 + 1];

    for (int i = len2; i != 0; --i)      /// 最大子串长度为 i ，
    {
        for (int j = 0; j != len2 - i + 1; ++j)   /// 逐个遍历 str2 的长度为 i 的子串
        {
            memcpy(substring, str2 + j, i);
            substring[i] = '\0';

            if (NULL != strstr(str1, substring))
                return substring;
        }
    }

    return NULL;
}
