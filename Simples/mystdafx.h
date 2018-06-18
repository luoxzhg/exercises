#pragma once
#include <map>
#include <string>
#include <vector>
#ifndef MYSTDAFX_H_INCLUDED
#define MYSTDAFX_H_INCLUDED

void  word_transform(ifstream &input, ifstream &map_file);

void  buildMap(map<string, string> &word_map, ifstream &map_file);

void  eatspace(istream &is);

vector<int>  *getVector(void);

void getValue(vector<int> &, istream &is = cin);

void printVector(vector<int> &, ostream &os = cout);

// FIXME: 对函数的引用
// int (&a)(void) = getchar;

template <typename T> inline int
compare(const T &v1, const T &v2)
{
    return v1 < v2 ? -1 : (v2 < v1 ? 1 : 0);
}
//=====================================================
//inline double square(double);
inline double square(double x) {return x * x;}

struct mystruct {
    char temp[10];
    void output(void) {std::cout << temp << endl;}
};

template <typename Func>
void execute(Func func)
{
    std::cout << "In function: template<typename> void execute(Func) " << endl;
    func();
}

/** \brief
 *
 * \param void
 * \return void
 *
 */
inline void myfunc(void)
{
    std::cout << "In function void myfunc(void)" << endl;
}

template<typename T>
class  List {
public:
    bool isEmpty()const {return true;}
};

template<typename T>
class  Stack : private List<T> {
public:
    // \fixme: 为什么需要 this
    bool isEmpty()const {return this->isEmpty();}
};

////////////////////////////////////////////////////////////////
/// @param cnt 为最大字符数，不包括结尾空字符，dest需要为结尾空字符保留空间
/// 即，cnt 最大为 bufsize - 1
char *mystrncpy(char *dest, const char *src, size_t cnt);

template<typename T, int n>
constexpr int countof(const T(&)[n])
{
    return n;
}

// 日期处理
inline bool isLeapYear(int year)
{
    return (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)) ;
}

inline int  realDaysOfMonth(int year, int month)
{
    static const int daysOfMonth[] = {
        0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
    };
    return (isLeapYear(year) && 2 == month) ? 29 : daysOfMonth[month];
}

void  output_factor(int num, ostream &os = std::cout);

class Int;
Int doSomething(Int);

class Int {
    //friend Int operator+(Int a, Int b) { return Int(a.i + b.i);}
    friend ostream &operator<<(ostream &os, Int a) { return os << a.i;}
public:
    Int(int &a): i(a) {}
    ///? 没有支持引用限定
    //Int& operator=(const Int& rhs) { i = rhs.i; return *this;}
private:
    int &i;
};

///=============================================================================
class Base1
{
    public:
    Base1() {cout << "Base1" << endl; }
    virtual ~Base1() { cout << "~Base1" << endl; }
};

class Base2
{
    public:
    Base2() { cout << "Base2" << endl; }
    virtual ~Base2() { cout << "~Base2" << endl; }
};

class Member
{
public:
    Member() { cout << "Member" << endl; }
    ~Member() { cout << "~Member" << endl; }
};
class  Derived:public Base1, public Base2
{
    public:
    Derived() { cout << "Derived" << endl; }
    ~Derived() {cout << "~Derived" << endl; }
    private:
        Member _m;
};

#endif // MYSTDAFX_H_INCLUDED
