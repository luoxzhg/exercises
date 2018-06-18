#ifndef MYBITSET_H_INCLUDED
#define MYBITSET_H_INCLUDED

// �ļ�����
#include <stdbool.h>
#include <stddef.h>



// ԭ������

void set_bit(char bit_array[], unsigned  pos);

void  reset_bit(char bit_array[], unsigned pos);

inline void  assign_bit(char bit_array[], unsigned pos, bool val);

bool   get_bit(char bit_array[], unsigned pos);




inline void   assign_bit(char bit_array[], unsigned pos, bool val)
{
    (val) ? set_bit(bit_array, pos) : reset_bit(bit_array, pos);
}

#endif // MYBITSET_H_INCLUDED
