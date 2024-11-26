#ifndef SHARED_PTR_H
#define SHARED_PTR_H

#include "Swap.h"
#include <cstddef>


template<typename T>
class weak_ptr;

template<typename T>
class shared_ptr
{
    using U = remove_extent_t<T>;
private:
    U* ptr;
    struct ControlBlock
    {
        size_t strongCount;
        size_t weakCount;
        explicit ControlBlock(const size_t strong = 0, const size_t weak = 0)
            : strongCount(strong), weakCount(weak) {}
    };
    ControlBlock* cb;
    void release()
    {
        if (cb) {
            if (--cb->strongCount == 0) {
                delete ptr;
                if (cb->weakCount == 0) {
                    delete cb;
                }
            }
        }
    }
    void retain()
    {
        if (cb) {
            ++cb->strongCount;
        }
    }
    friend class weak_ptr<T>;
    T* get() const { return ptr; }
    friend bool operator<(const shared_ptr& lhs, const shared_ptr& rhs)
    {
        return lhs.get() < rhs.get();
    }
    friend bool operator<=(const shared_ptr& lhs, const shared_ptr& rhs)
    {
        return lhs.get() <= rhs.get();
    }
    friend bool operator>(const shared_ptr& lhs, const shared_ptr& rhs)
    {
        return lhs.get() > rhs.get();
    }
    friend bool operator>=(const shared_ptr& lhs, const shared_ptr& rhs)
    {
        return lhs.get() >= rhs.get();
    }
    friend bool operator==(std::nullptr_t, const shared_ptr& ptr) {
        return ptr.get() == nullptr;
    }
    friend bool operator!=(std::nullptr_t, const shared_ptr& ptr) {
        return ptr.get() != nullptr;
    }
public:
    inline void swap(shared_ptr& other) noexcept {
        my_swap(ptr, other.ptr);
        my_swap(cb, other.cb);
    }
    //конструкторы
    shared_ptr() : ptr(nullptr), cb(nullptr) {}
    explicit shared_ptr(U* other) : ptr(other)
    {
        if (ptr) {
            cb = new ControlBlock(1, 0);
        } else {
            cb = nullptr;
        }
    }
    explicit shared_ptr(const weak_ptr<T>& weak) : ptr(weak.ptr), cb(weak.cb) {
        if (cb) {
            ++(cb->strongCount);
        }
    }
    shared_ptr(const shared_ptr& other) : ptr(other.ptr), cb(other.cb)
    {
        retain();
    }
    shared_ptr(shared_ptr&& other) noexcept : ptr(other.ptr), cb(other.cb)
    {
        other.ptr = nullptr;
        other.cb = nullptr;
    }
    explicit shared_ptr(U* p, ControlBlock* controlBlock)
        : ptr(p), cb(controlBlock)
    {
        if (cb) {
            ++cb->strongCount;
        }
    }

    ~shared_ptr()
    {
        release();
    }
    //методы
    int use_count() const { return cb ? cb->strongCount : 0; }
    bool unique() const { return use_count() == 1; }
    void reset(T* other = nullptr)
    {
        release();
        if (other) {
            ptr = other;
            cb = new ControlBlock(1, 0);
        } else {
            ptr = nullptr;
            cb = nullptr;
        }
    }
    //операторы
    shared_ptr& operator=(const shared_ptr& other)
    {
        if (this != &other) {
            release();
            ptr = other.ptr;
            cb = other.cb;
            retain();
        }
        return *this;
    }

    shared_ptr& operator=(shared_ptr&& other) noexcept {
        if (this != &other) {
            release();
            ptr = other.ptr;
            cb = other.cb;
            other.ptr = nullptr;
            other.cb = nullptr;
        }
        return *this;
    }

    U& operator*() const { return *ptr; }
    U* operator->() const { return ptr; }
    U& operator[](int index) const { return ptr[index]; }
    bool operator==(const shared_ptr& other) const { return ptr == other.ptr; }
    bool operator!=(const shared_ptr& other) const { return ptr != other.ptr; }
    bool operator==(std::nullptr_t) const { return ptr == nullptr; }
    bool operator!=(std::nullptr_t) const { return ptr != nullptr; }
};

template<typename T, typename... Args, typename = std::enable_if_t<!std::is_array_v<T>>>
shared_ptr<T> make_shared(Args&&... args) {
    return shared_ptr<T>(new T(std::forward<Args>(args)...));
}

template<typename T>
shared_ptr<T> make_shared(const size_t size) {
    using BaseType = std::remove_extent_t<T>;
    static_assert(!std::is_same_v<BaseType, void>, "Cannot create an array of void.");
    return shared_ptr<T>(new BaseType[size]);
}

template<typename T, typename... Args>
shared_ptr<T> make_shared(const size_t size, Args&&... args) {
    using BaseType = std::remove_extent_t<T>;
    static_assert(!std::is_same_v<BaseType, void>, "Cannot create an array of void.");
    BaseType* ptr = new BaseType[size];
    for (size_t i = 0; i < size; ++i) {
        ptr[i] = BaseType(std::forward<Args>(args)...);
    }
    return shared_ptr<T>(ptr);
}


#endif //SHARED_PTR_H
