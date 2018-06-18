#include "../include/HasPtr.h"
#include <iostream>
#include <algorithm>
using namespace std;
HasPtr::HasPtr()
{
    cout << "default constructor" << endl;
    //ctor
}

HasPtr::~HasPtr()
{
    cout << "destructor" << endl;
    free();
    //dtor
}

HasPtr::HasPtr(const HasPtr& other)
{
    first = alloc.allocate(other.last - other.first);
    last = uninitialized_copy(other.first, other.last, first);
    cap = last;
    //copy ctor
}

HasPtr& HasPtr::operator=(const HasPtr& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator

    if (capacity() >= rhs.size())
    {
        auto dest = first;
        for (auto it = rhs.cbegin(); it != rhs.cend(); )
        {
            *dest++ = *it++;
        }
    }
    else
    {
        free();
        first = alloc.allocate(rhs.size());
        last = uninitialized_copy(rhs.cbegin(), rhs.cend(), first);
        cap = last;
    }

    return *this;
}

void HasPtr::free()
{
    if (first == nullptr)
        return;
    for (auto elem = last; elem != last; )
        alloc.destroy(--elem);
    alloc.deallocate(first, cap - first);
}



