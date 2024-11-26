#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include <iostream>
#include "Unique_Ptr.h"

template <typename T>
class DynamicArray {
private:
    int size{};
    int capacity{};
    unique_ptr<T[]> elements;

    inline void Reserve(int newCapacity) {
        if (newCapacity <= capacity) {
            return;
        }

        unique_ptr<T[]> newElements = unique_ptr<T[]>(new T[newCapacity]);
        for (int i = 0; i < size; i++) {
            newElements[i] = elements[i];
        }
        elements = move(newElements);
        capacity = newCapacity;
    }

public:
    DynamicArray() : size(0), capacity(0), elements(nullptr) {}

    DynamicArray(const unique_ptr<T[]>& items, int count) : DynamicArray(count) {
        if (items == nullptr) {
            throw std::out_of_range("invalid items argument for constructor");
        }
        for (int i = 0; i < count; i++) {
            elements[i] = items[i];
        }
    }

    DynamicArray(T* items, int count) : DynamicArray(count) {
        if (!items) {
            throw std::out_of_range("invalid items argument for constructor");
        }
        for (int i = 0; i < count; i++) {
            elements[i] = items[i];
        }
    }

    explicit DynamicArray(const int size) : size(size), capacity(size + 1) {
        if (size < 0) {
            throw std::out_of_range("invalid size argument");
        }
        elements = unique_ptr<T[]>(new T[size]);
    }

    DynamicArray(const DynamicArray& dynamicArray) = delete;

    DynamicArray &operator=(const DynamicArray &dynamicArray) = delete; // Запрещаем копирование

    DynamicArray &operator=(DynamicArray &&dynamicArray) noexcept
    {
        if (this != &dynamicArray)
        {
            size = dynamicArray.size;
            capacity = dynamicArray.capacity;
            elements = move(dynamicArray.elements); // Перемещаем уникальный указатель
            dynamicArray.size = 0;
            dynamicArray.capacity = 0;
        }
        return *this;
    }

    ~DynamicArray() = default;

    T Get(int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("invalid index");
        }
        return elements[index];
    }

    int GetSize() const {
        return size;
    }

    void Set(const T& value, int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("invalid index");
        }
        elements[index] = value;
    }

    void Resize(const int newSize) {
        if (newSize < 0) {
            throw std::out_of_range("invalid newSize");
        }

        if (newSize > capacity) {
            Reserve(newSize * 2);
        } else if (newSize < size) {
            auto newElements = unique_ptr<T[]>(new T[newSize]);
            for (int i = 0; i < newSize; i++) {
                newElements[i] = elements[i];
            }
            elements = move(newElements);
            capacity = newSize;
        }
        size = newSize;
    }

    T& operator[](int index)
    {
        if(size<=index || size < 0)
        {
            throw std::out_of_range("Invalid index");
        }
        return elements[index];
    }

    const T& operator[](int index) const
    {
        if(size<=index || size < 0)
        {
            throw std::out_of_range("Invalid index");
        }
        return elements[index];
    }
};

#endif // DYNAMICARRAY_H
