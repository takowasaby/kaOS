#pragma once

#include "memory.h"

template
<class T>
class Vec
{
public:
    using value_type = T;
    using size_type = unsigned int;

    size_type size() const noexcept
    {
        return size_;
    }
    void resize(size_type sz)
    {
        reserve(calcNewCapacity(capacity_, sz));
        while (size_ < sz && size_ < capacity_)
        {
            new(base_pointer_ + size_) T();
            ++size_;
        }
    }
    size_type capacity() const
    {
        return capacity_;
    }
    bool empty() const noexcept
    {
        return size_ == 0;
    }
    void reserve(size_type n)
    {
        if (n < size_) return;
        if (n == capacity_) return;
        T* newMemoryArea = reinterpret_cast<T *>(malloc(sizeof(T) * n));
        if (newMemoryArea == nullptr) return;
        memcpy(newMemoryArea, base_pointer_, size_ * sizeof(T));
        free(base_pointer_);
        base_pointer_ = newMemoryArea;
        capacity_ = n;
    }
    void shrink_to_fit()
    {
        reserve(size_);
    }

    T& at(size_type n)
    {
        if (n >= size_) return *base_pointer_;
        return *(base_pointer_ + n);
    }
    const T& at(size_type n) const
    {
        return at(n);
    }
    T& operator[](size_type n)
    {
        return at(n);
    }
    const T& operator[](size_type n) const
    {
        return at(n);
    }
    T& front()
    {
        return at(0);
    }
    const T& front() const
    {
        return front();
    }
    T& back()
    {
        return at(size_ - 1);
    }
    const T& back() const
    {
        return back();
    }

    T* data() noexcept
    {
        return base_pointer_;
    }
    const T* data() const noexcept
    {
        return data();
    }

    void push_back(const T& x)
    {
        reserve(calcNewCapacity(capacity_, size_ + 1));
        new(base_pointer_ + size_) T(x);
        ++size_;
    }
    template <class... Args>
    T& emplace_back(Args&&... args)
    {
        reserve(calcNewCapacity(capacity_, size_ + 1));
        new(base_pointer_ + size_) T(args...);
        ++size_;
        return back();
    }

    void pop_back()
    {
        if (size_ == 0) return;
        (base_pointer_ + (size_ - 1))->~T();
        --size_;
    }
    void clear()
    {
        while(size_ != 0)
        {
            pop_back();
        }
    }

    Vec() :
        base_pointer_(nullptr),
        size_(0),
        capacity_(0)
    {
        reserve(8);
    }
    explicit Vec(size_type n) :
        base_pointer_(nullptr),
        size_(0),
        capacity_(0)
    {
        resize(n);
    }
    Vec(size_type n, const T& value) :
        base_pointer_(nullptr),
        size_(0),
        capacity_(0)
    {
        reserve(n);
        while (size_ < n)
        {
            push_back(value);
        }
    }
    template <class... Args>
    Vec(size_type n, Args&&... args) :
        base_pointer_(nullptr),
        size_(0),
        capacity_(0)
    {
        reserve(n);
        while (size_ < n)
        {
            emplace_back(args...);
        }
    }
    ~Vec()
    {
        clear();
    }
    Vec(const Vec<T>& x) :
        base_pointer_(nullptr),
        size_(0),
        capacity_(0)
    {
        reserve(x.capacity_);
        memcpy(base_pointer_, x.base_pointer_, x.size_);
        size_ = x.size_;
    }
    Vec<T>& operator=(const Vec<T>& x)
    {
        clear();
        reserve(x.capacity_);
        memcpy(base_pointer_, x.base_pointer_, x.size_);
        size_ = x.size_;
    }

private:
    T* base_pointer_;
    size_type size_;
    size_type capacity_;

    static size_type calcNewCapacity(size_type oldCapacity, size_type newSize)
    {
        size_type newCapacity = (oldCapacity ? oldCapacity : 1);
        while(newCapacity < newSize)
        {
            newCapacity <<= 1;
        }
        return newCapacity;
    }

};

template <class T>
bool operator==(const Vec<T>& x, const Vec<T>& y)
{
    if (x.size() != y.size()) return false;
    if (x.capacity() != y.capacity()) return false;
    typename Vec<T>::size_type size = x.size();
    bool result = false;
    for (typename Vec<T>::size_type i = 0; i < size; i++)
    {
        result = result || x[i] == y[i];
    }
    return result;
}
