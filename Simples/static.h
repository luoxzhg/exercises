#ifndef STATIC_H
#define STATIC_H
#include <iostream>

template<typename T> inline int
compare(const T& a, const T& b)
{
    std::cout << "In first!\n";
    std::cout << sizeof(T);
    return a==b ? 0
                : a>b ? 1 : -1;
}
///////////////////////////////////

template<typename T>
class B
{
public:
    B(){std::cout << "默认构造函数！" << std::endl;}
    B(int i){std :: cout << "int 参数构造函数！" << std::endl; }
    B(const B& oth){std :: cout << "copy 构造函数！" << std::endl;}
    virtual void f(){std::cout << "In class B!\n";}
    virtual ~B(){}
};

template<typename T>
class D : public B<T>
{
public:
    void f(){std::cout << "In class D!\n";}
};

template<typename T> void
f(B<T>* p)
{
    p->f();
}
////////////////////////////////////

template<typename T> void

g(B<T>* pb, D<T>* pd)
{
    f(pb);
    f(pd);
}
#endif
