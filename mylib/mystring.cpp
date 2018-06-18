#include "mystring.h"

#if 1  /// special member functions
String::String() noexcept
    : _p_data(_local_buf), _length(0)
{
    *_p_data = '\0';
}

String::~String() noexcept
{
    //dtor
    dealloc_mem();
}

String::String(const String& other) noexcept
{
    //copy ctor
    copy_data(other);
}

String& String::operator=(const String& rhs) noexcept
{
    if (this == &rhs || _p_data == rhs._p_data)
    { return *this; } // handle self assignment
    // assignment operator
    dealloc_mem();  // 由于不会抛出异常，因此可以直接释放

    copy_data(rhs);
    return *this;
}

String::String(String&& other)noexcept
{
    move_data(std::move(other));
}

String& String::operator=(String&& rhs)noexcept
{
    if (this == &rhs) return *this;

    dealloc_mem();
    move_data(std::move(rhs));

    return *this;
}

#endif // 1

#if 1  /// 普通构造函数和操作符重载
String::String(const_pointer p)
    : _p_data(_local_buf)
{
    _length = strlen(p);
    if (_length > _local_capacity)
    {
        reset_allocated(alloc_mem(_length), _length);
    }
    copy_from_pointer(_p_data, p, _length);
}

String& String::operator=(const_pointer p)
{
    // TODO: remain to optimize
    String temp(p);
    swap(temp);
    return *this;
}

String& String::operator+=(const String& rhs)
{
    auto newLength = length() + rhs.length();
    if (!unique() || newLength > capacity())
        set_to_unique(newLength);

    copy_from_pointer(end(), rhs.cbegin(), rhs.length());
    _length = newLength;
    return *this;
}
#endif // 1

#if 1  /// 一般成员
void  String::reserve(size_type new_cap)
{
    if (new_cap <= capacity())
    { return; }

    set_to_unique(new_cap);
}

void  String::swap(String& other) noexcept
{
    using std::swap;
    bool  flag1 = is_in_buf(), flag2 = other.is_in_buf();

    swap(_local_buf, other._local_buf);
    swap(_p_data, other._p_data);

    if (flag1)
        other._p_data = other._local_buf;

    if (flag2)
        _p_data = _local_buf;
}
#endif // 1

#if 1  /// 友元
std::ostream& operator<<(std::ostream& os, const String& s)
{
    return os << s.data();
}

String  operator+(const String& lhs, const String& rhs)
{
    String temp = lhs;
    temp += rhs;
    return temp;
}
#endif // 1
