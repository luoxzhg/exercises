// include�ļ�
#include "myString.h"

// using ����


//-----------------------------------------

// ȫ�ֱ���


//-----------------------------------------

// ����ԭ������

// ----------------------------------------
using std::istream;
myString& myString::operator+=(const myString& rhs)
{
    size_t  len = m_size + rhs.m_size;
    char* temp = new char[len + 1];
    strcpy(temp, m_str);
    strcat(temp + m_size, rhs.m_str);
    delete[] m_str;
    m_size = len;
    m_str = temp;

    return *this;
}

istream&  operator>>(istream& is, myString& str)
{
//    int  ch;
//    while (ch=is.get(), )
    return is;
}
