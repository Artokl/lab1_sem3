#ifndef WEAK_PTR_H
#define WEAK_PTR_H

#include "Additional_Structures.h"
#include "Shared_Ptr.h"
#include "Swap.h"
#include <cstddef>

template<typename T>
class weak_ptr
{
    using U = remove_extent_t<T>;
private:
    U* ptr;
    typename shared_ptr<T>::ControlBlock* cb;

    void release()
    {
        if (cb) {
            if (--cb->weakCount == 0 && cb->strongCount == 0) {
                delete cb;
            }
        }
    }

    void retain()
    {
        if (cb) {
            ++cb->weakCount;
        }
    }

public:
    friend class shared_ptr<T>;
    //конструкторы
    weak_ptr() : ptr(nullptr), cb(nullptr) {}
    explicit weak_ptr(const shared_ptr<T>& shared) : ptr(shared.ptr), cb(shared.cb)
    {
        retain();
    }
    weak_ptr(const weak_ptr& other) : ptr(other.ptr), cb(other.cb)
    {
        retain();
    }
    weak_ptr(weak_ptr&& other) noexcept : ptr(other.ptr), cb(other.cb)
    {
        other.ptr = nullptr;
        other.cb = nullptr;
    }
    ~weak_ptr()
    {
        release();
    }
    //методы
    bool expired() const
    {
        return cb == nullptr || cb->strongCount == 0;
    }
    shared_ptr<T> lock() const
    {
        if (cb == nullptr || cb->strongCount == 0) {
            return shared_ptr<T>();
        }
        return shared_ptr<T>(ptr, cb);
    }
    size_t use_count() const
    {
        return cb ? cb->weakCount : 0;
    }
    void reset()
    {
        release();
        ptr = nullptr;
        cb = nullptr;
    }
    void swap(weak_ptr& other) noexcept
    {
        my_swap(ptr, other.ptr);
        my_swap(cb, other.cb);
    }
    //операторы
    weak_ptr& operator=(const weak_ptr& other)
    {
        if (this != &other) {
            release();
            ptr = other.ptr;
            cb = other.cb;
            retain();
        }
        return *this;
    }
    weak_ptr& operator=(weak_ptr&& other) noexcept
    {
        if (this != &other) {
            release();
            ptr = other.ptr;
            cb = other.cb;
            other.ptr = nullptr;
            other.cb = nullptr;
        }
        return *this;
    }
};

#endif // WEAK_PTR_H
