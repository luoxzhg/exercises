#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <numeric>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include "template.h"
#include "template.h"
#include <vector>
#include <thread>
#include <string>
#include <array>

using namespace std;
using namespace std::rel_ops;

template<typename T>
class cls
{
public:
    cls() = default;
    cls(cls &oth) : i(oth.i)
    {
        cout << "lvalue ctor!\n";
    }
    cls(cls && oth): i(oth.i)
    {
        cout << "rvalue ctor!\n";
    }
    ~cls() = default;
protected:

private:
    int i = 0;
};

struct myStruct
{
    //myStruct(int i) : i_(i) { cout << "In ctor!\n"; }
    char i_;
    char j_;
    double d_;

};

template <typename T>
class Ptr
{
    T p;
public:
    Ptr(int = 0) : p(0)  { cout << "Ĭ�Ϲ��캯��\n"; }

    Ptr(const Ptr &oth): p(oth.p)  {  cout << "���ƹ��캯��\n"; }

    Ptr(T && oth) : p(oth.p)   { cout << "move���캯��\n"; oth.p = nullptr;}

    ~Ptr()  { cout << "��������\n"; }
};

template <typename T>
Ptr<T>  func(const Ptr<T> &oth)
{
    auto  temp = oth;
    return std::move(temp);
}

int main(void)
{
    std::cout << ("��ӭ!\n");


    Ptr<int>  p1;
    auto p2 = func(p1);


}
