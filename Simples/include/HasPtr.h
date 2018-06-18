#ifndef HASPTR_H
#define HASPTR_H
#include <iterator>
#include <memory>
class HasPtr
{
    friend void swap(HasPtr& lhs, HasPtr& rhs);
public:
    HasPtr();
    ~HasPtr();
    HasPtr(const HasPtr& other);
    HasPtr(HasPtr&&);
    //HasPtr& operator=(HasPtr temp);
    HasPtr& operator=(const HasPtr& other);
    //HasPtr& operator=(HasPtr&&);

    int* begin() { return first;}
    const int* cbegin()const {return first;}
    int* end() { return last;}
    const int* cend() const {return last;}
    size_t size() const { return last - first; }
    size_t capacity() const { return cap - first; }
protected:
private:
    std::allocator<int> alloc;
    int* first = nullptr;
    int* last = nullptr;
    int* cap = nullptr;

    // utility member
    void destruct();
    void free();
};

// inline member
inline void swap(HasPtr& lhs, HasPtr& rhs)
{
    using std::swap;
    swap(lhs.first, rhs.first);
    swap(lhs.last, rhs.last);
    swap(lhs.cap, rhs.cap);
}


#endif // HASPTR_H
