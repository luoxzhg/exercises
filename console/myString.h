#ifndef MYSTRING_H
#define MYSTRING_H

#include <iostream>
#include <utility>
#include <cassert>
#include <cstring>
#include <stdexcept>

// using 声明
using namespace std::rel_ops;


inline void func1(void)
{
    std::cout << "I am in func1\n";
}

// class definition

class myString
{
public:
    /** Default constructor */
    myString();

    /// 这是一个可转换函数
    myString(const char*);

    /** Copy constructor
     *  \param other Object to copy from
     */
    myString(const myString& other);

    /// move ctor
    myString(myString&& oth) noexcept;

    /** Default destructor */
    ~myString() { delete[] m_str;}

    /** Assignment operator
     *  \param other Object to assign from
     *  \return A reference to this
     */
    myString& operator=(const myString& other);
    myString& operator=(myString&& old) noexcept;


    myString& operator+=(const myString& other);


    char& operator[](std::size_t pos) noexcept { assert(pos < m_size); return m_str[pos];}
    const char& operator[](std::size_t pos)const noexcept { assert(pos < m_size); return m_str[pos];}

    std::size_t  size()const noexcept{ return m_size; }
    std::size_t  length()const noexcept{ return m_size; }
    const char* c_str()const noexcept{ return m_str; }

    /// friend functions
    friend std::istream&  operator>>(std::istream& is, myString& str);
    friend std::ostream&  operator<<(std::ostream& os, const myString& str);
    friend myString  operator+(const myString& lhs, const myString& rhs);

    friend void  swap(myString& lhs, myString& rhs) noexcept;
    friend bool  operator==(const myString& lhs, const myString& rhs) noexcept;
    friend bool  operator<(const myString& lhs, const myString& rhs) noexcept;


protected:
private:
//    void  release() { delete[] m_str; }
private:
    std::size_t m_size = 0; //!< Member variable "m_size"
    char* m_str; //!< Member variable "m_str"
};

/// inline 成员及其友元

/// 构造函数
inline myString::myString()
                        :m_size(0),m_str(nullptr)
{
    //ctor
    m_str = new char[1];
    *m_str = '\0';
}

inline myString::myString(const char* str):m_str(nullptr)
{
    if (str==nullptr)
        throw std::invalid_argument("myString ctor, nullptr is invalid\n");
    m_size = strlen(str);
    m_str = new char[m_size + 1];   // 可能抛出异常
    strcpy(m_str, str);
}

inline myString::myString(const myString& other)
                        :m_size(other.m_size), m_str(nullptr)
{
    //copy ctor
    m_str = new char[m_size + 1];
    strcpy(m_str, other.m_str);
}

inline myString::myString(myString&& old) noexcept
                        :m_size(old.m_size), m_str(old.m_str)
{
    old.m_size = 0;
    old.m_str = nullptr;
}

/// copy赋值操作符
inline myString& myString::operator=(const myString& rhs)
{
    //if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    myString  temp = rhs;
    swap(*this, temp);
    return *this;
}

/// move赋值操作符
inline myString& myString::operator=(myString&& old) noexcept
{
    m_size = old.m_size;
    m_str = old.m_str;
    old.m_str = nullptr;
    return *this;
}

inline  std::ostream& operator<<(std::ostream& is, const myString& str)
{
    is << str.m_str;
    return is;
}

inline  myString operator+(const myString& lhs, const myString& rhs)
{
    myString temp = lhs;
    return temp += rhs;
}

inline void swap(myString& lhs, myString& rhs) noexcept
{
    using std::swap;
    swap(lhs.m_size, rhs.m_size);
    swap(lhs.m_str, rhs.m_str);
}

inline  bool  operator==(const myString& lhs, const myString& rhs) noexcept
{
    if (0 == strcmp(lhs.m_str, rhs.m_str))
        return true;
    else
        return false;
}

inline  bool  operator<(const myString& lhs, const myString& rhs) noexcept
{
    if (0 > strcmp(lhs.m_str, rhs.m_str))
        return true;
    else
        return false;
}

#endif // MYSTRING_H
