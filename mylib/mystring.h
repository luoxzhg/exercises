/// ��ʵ��ʵ�� SSO (small string optimization)�Ż��� COW (copy on write)�Ż�
/// ��ʵ����û��ģ�廯.�洢 char �����ַ�
/// ��ʵ����û��ʵ�� thread-safe
/// @author luoxzhg#live.com

#pragma once
#ifndef MY_STRING_H
#define MY_STRING_H

#include <cassert>
#include <iterator>
#include <iosfwd>
#include <string.h>

class String final
{
#if 1   /// friends
    friend std::ostream& operator<<(std::ostream& os, const String& s);
    friend String  operator+(const String& lhs, const String& rhs);
#endif // 1

public: /// ���ͱ����;�̬����
#if 1
    using  value_type   = char;
    using  reference    = value_type&;
    using  const_reference = const value_type&;
    using  pointer      = value_type*;
    using  const_pointer  = const value_type*;
    using  iterator       = value_type*;
    using  const_iterator = const value_type*;
    using  reverse_iterator = std::reverse_iterator<iterator>;
    using  const_reverse_iterator = std::reverse_iterator<const_iterator>;

    using  size_type    = size_t;

    static constexpr size_type nops = static_cast<size_type>(-1);
#endif // 1

public: /// special members
#if 1
    String() noexcept;
    ~String() noexcept;

    String(const String&) noexcept;
    String& operator=(const String&) noexcept;

    String(String&& other)noexcept;
    String& operator=(String&& rhs)noexcept;
#endif // 1

public: /// ��ͨ���캯���Ͳ���������
#if 1
    String(const_pointer p);
    String& operator=(const_pointer p);
    String& operator+=(const String& lhs);
#endif // 1

public:  /// һ���Ա
#if 1

    bool  empty() const noexcept
    { return *_p_data == '\0';}

    void clear() noexcept
    { dealloc_mem(); set_to_empty(); }

    size_type  length() const noexcept
    { return  _length; }

    size_type  capacity() const noexcept
    { return  is_in_buf() ? (size_type)_local_capacity : _allocated_capacity; }

    void  reserve(size_type new_cap);

    /// ��ȡ C-�ַ���
    const_pointer data() const noexcept {  return _p_data; }
    const_pointer c_str()const noexcept {  return data(); }

    /// swap member
    void  swap(String& other) noexcept;
#endif // 1

public:  /// ��ȡ������
#if 1
    const_iterator cbegin() const noexcept { return _p_data; }
    const_iterator begin() const noexcept { return cbegin(); }

    iterator begin() noexcept { return _p_data; }

    const_iterator cend() const noexcept { return _p_data + length(); }
    const_iterator end() const noexcept { return cend(); }

    iterator end() noexcept { return _p_data + length(); }
#endif // 1

private: /// private assistant member functions
#if 1
    bool is_in_buf() const noexcept
    {
        return _p_data == _local_buf;
    }

    bool is_full()const noexcept
    {
        return length() == capacity();
    }
    // user_count ֻ�ܵ��ַ����ڶ���ʱʹ�ã�ʹ�� _allocated_capacity
    size_type& user_count() const noexcept
    {
        assert(!is_in_buf());
        return *(size_type *)(_p_data + capacity() + 1);
    }

    value_type *alloc_mem(size_type cap)
    {
        assert(cap > _local_capacity);
        return new value_type[cap + 1 + sizeof(size_type)];
    }

    /// ԭ������봦�ڿ�״̬��p��������ַ������ȴ��ڻ���������
    void reset_allocated(value_type *p, size_type new_cap) noexcept
    {
        _p_data = p;
        _allocated_capacity = new_cap;
        user_count() = 1;
    }

    bool  unique() const noexcept
    {  return is_in_buf() || user_count() == 1; }

    // new_cap ��Ҫ���� _local_capacity, _length ��Ҫ������Ч
    void set_to_unique(size_type new_cap)
    {
        auto pnew = alloc_mem(new_cap);
        copy_from_pointer(pnew, _p_data, _length);
        dealloc_mem();
        reset_allocated(pnew, new_cap);
    }

    /// �����������ݣ��Ա�������ַ���
    void  dealloc_mem() noexcept
    {
        if (is_in_buf())  return;

        if (unique())
            delete[] _p_data;
        else
            --user_count();
    }

    /// �������Ķ�������Ϊ��
    void  set_to_empty() noexcept
    {
        _p_data = _local_buf;
        *_p_data = '\0';
        _length = 0;
    }
    /// copy-construct
    void copy_data(const String& other) noexcept
    {
        _length = other._length;

        if (other.is_in_buf())
            copy_to_buf(other);
        else
            copy_to_allocated(other);
    }

    /// �����Ƶ� String ���ַ���λ�� _local_buf
    void copy_to_buf(const String& other) noexcept
    {
        _p_data = _local_buf;
        copy_from_pointer(_p_data, other._p_data, _length);
    }

    /// �����Ƶ� String ���ַ���λ�ڶ���
    void copy_to_allocated(const String& other) noexcept
    {
        // �ѷ����ַ�������Ҫ������������
        _p_data = other._p_data;
        _allocated_capacity = other._allocated_capacity;
        ++other.user_count();
    }

    /// ��Ҫ������ַ�������
    void copy_from_pointer(pointer dest,
                        const_pointer src, size_type n) noexcept
    {
        memcpy(dest, src, (n + 1)*sizeof(value_type));
    }

    /// move data from String object
    void move_data(String&& other) noexcept
    {
        _length = other._length;
        if (other.is_in_buf())
            copy_to_buf(other);
        else
            move_to_allocated(std::move(other));
    }

    void move_to_allocated(String&& other) noexcept
    {
        _p_data = other._p_data;
        _allocated_capacity = other._allocated_capacity;
        other.set_to_empty();
    }


#endif // 1

private: /// data
#if 1
    pointer  _p_data;  // �ַ���ʵ��λ��
    size_type  _length;
    // FIXME: why 16?
    // �����ǵ��Ժ�Ϊģ�廯��׼��
    enum {_local_capacity = 16 / sizeof(value_type) - 1};
    // �������ݽṹ
    union
    {
        value_type _local_buf[_local_capacity + 1];

        size_type  _allocated_capacity;
    };
#endif // 1
};

namespace std
{
    template<>
    inline void swap(String& lhs, String& rhs) noexcept
    {
        lhs.swap(rhs);
    }
}

#endif // MY_STRING_H
