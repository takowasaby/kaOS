#pragma once

#include "memory/memory.h"

template
<class T>
class Queue
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
        if (sz <= size_) return;
        if (sz > capacity_) 
        {
            reserve(calcNewCapacity(capacity_, sz));
        }
        size_type initializeEnd = newIndex(capacity_, back_ + sz);
        while(back_ != initializeEnd)
        {
            new(base_pointer_ + back_) T();
            back_ = newIndex(capacity_, back_ + 1);
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
        if (!empty())
        {
            memcpy(newMemoryArea + front_, base_pointer_ + front_, sizeof(T));
            size_type newi = front_ + 1;
            for (size_type i = front_ + 1; i != back_; i = newIndex(capacity_, i + 1), newi = newIndex(n, newi + 1))
            {
                memcpy(newMemoryArea + newi, base_pointer_ + i, sizeof(T));
            }
            back_ = newi;
        }
        free(base_pointer_);
        base_pointer_ = newMemoryArea;
        capacity_ = n;
    }
    void shrink_to_fit()
    {
        reserve(size());
    }

    T& at(size_type n)
    {
        if (n >= size_) return *(base_pointer_ + front_);
        return *(base_pointer_ + newIndex(capacity_, front_ + n));
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

    void push_back(const T& x)
    {
        reserve(calcNewCapacity(capacity_, size_ + 1));
        new(base_pointer_ + back_) T(x);
        back_ = newIndex(capacity_, back_ + 1);
        ++size_;
    }
    void enqueue(const T& x)
    {
        push_back(x);
    }
    template <class... Args>
    T& emplace_back(Args&&... args)
    {
        reserve(calcNewCapacity(capacity_, size_ + 1));
        new(base_pointer_ + back_) T(args...);
        back_ = newIndex(capacity_, back_ + 1);
        ++size_;
        return back();
    }

    void pop()
    {
        if (size_ == 0) return;
        (base_pointer_ + front_)->~T();
        front_ = newIndex(capacity_, front_ + 1);
        --size_;
    }
    T dequeue()
    {
        if (size_ == 0) return T();
        T popValue = *(base_pointer_ + front_);
        (base_pointer_ + front_)->~T();
        front_ = newIndex(capacity_, front_ + 1);
        --size_;
        return popValue;
    }
    void clear()
    {
        while(size_ != 0)
        {
            pop();
        }
    }

    Queue() :
        base_pointer_(nullptr),
        size_(0),
        capacity_(0),
        front_(0),
        back_(0)
    {
        reserve(8);
    }
    explicit Queue(size_type n) :
        base_pointer_(nullptr),
        size_(0),
        capacity_(0),
        front_(0),
        back_(0)
    {
        resize(n);
    }
    Queue(size_type n, const T& value) :
        base_pointer_(nullptr),
        size_(0),
        capacity_(0),
        front_(0),
        back_(0)
    {
        reserve(n);
        while (size_ < n)
        {
            push_back(value);
        }
    }
    template <class... Args>
    Queue(size_type n, Args&&... args) :
        base_pointer_(nullptr),
        size_(0),
        capacity_(0),
        front_(0),
        back_(0)
    {
        reserve(n);
        while (size_ < n)
        {
            emplace_back(args...);
        }
    }
    ~Queue()
    {
        clear();
    }
    Queue(const Queue<T>& x) :
        base_pointer_(nullptr),
        size_(0),
        capacity_(0),
        front_(0),
        back_(0)
    {
        reserve(x.capacity_);
        memcpy(base_pointer_, x.base_pointer_, x.capacity_);
        size_ = x.size_;
        front_ = x.front_;
        back_ = x.back_;
    }
    Queue<T>& operator=(const Queue<T>& x)
    {
        clear();
        reserve(x.capacity_);
        memcpy(base_pointer_, x.base_pointer_, x.capacity_);
        size_ = x.size_;
        front_ = x.front_;
        back_ = x.back_;
    }

private:
    T* base_pointer_;
    size_type size_;
    size_type capacity_;
    size_type front_;
    size_type back_;

    static size_type newIndex(size_type capacity, size_type index)
    {
        if (index >= capacity)
        {
            return index - capacity;
        }
        return index;
    }
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
bool operator==(const Queue<T>& x, const Queue<T>& y)
{
    if (x.size() != y.size()) return false;
    if (x.capacity() != y.capacity()) return false;
    typename Queue<T>::size_type size = x.size();
    bool result = false;
    for (typename Queue<T>::size_type i = 0; i < size; i++)
    {
        result = result || x[i] == y[i];
    }
    return result;
}
