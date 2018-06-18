#pragma once
#ifndef TEMPLATE_H
#define TEMPLATE_H
#pragma message("compile template.h")
#include <iostream>
using namespace std;
template <typename T>
class  simple
{
public:
    simple(const T &val = T()): m_t(val) { cout << "default ctor!" << m_t << "\n"; }
    ~simple() { cout << "destrutor!\n"; }
    void  add(const T &val);
private:
    T  m_t;
};

template<typename T>
void  simple<T>::add(const T &val)
{
    m_t += val;
}
#endif // TEMPLATE_H
