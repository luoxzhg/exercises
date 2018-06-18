// include文件
#include "mybitset.h"
#include <limits.h>
#include <assert.h>
//-----------------------------------------

// using 声明
//-----------------------------------------

// 全局变量
//-----------------------------------------
//int* a = (int*)0x11111111;

// function implementation

void   set_bit(char bit_array[], unsigned pos)
{
    assert(bit_array != NULL);
    unsigned  index = pos/CHAR_BIT;
    unsigned  offset = pos%CHAR_BIT;

    bit_array[index] |= (char)(1 << offset);

}

void   reset_bit(char bit_array[], unsigned pos)
{
    assert(bit_array != NULL);
    unsigned  index = pos/CHAR_BIT;
    unsigned  offset = pos%CHAR_BIT;

    bit_array[index] &= (char)(~(1 << offset));
}



bool  get_bit(char bit_array[], unsigned pos)
{
    assert(bit_array != NULL);
    unsigned  index = pos/CHAR_BIT;
    unsigned  offset = pos%CHAR_BIT;

    return  bit_array[index] & (1 << offset);
}
