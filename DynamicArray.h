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

    void Reserve(int newCapacity) {
        if (newCapacity <= capacity) {
            return;
        }

        unique_ptr<T[]> newElements = make_unique<T[]>(newCapacity);
        for (int i = 0; i < size; i++) {
            newElements[i] = elements[i];
        }
        elements = std::move(newElements);
        capacity = newCapacity;
    }

public:
    DynamicArray() : size(0), capacity(0), elements(nullptr) {}

    DynamicArray(T* items, int count) : DynamicArray(count) {
        if (!items) {
            throw std::out_of_range("invalid items argument for constructor");
        }
        for (int i = 0; i < count; i++) {
            elements[i] = items[i];
        }
    }

    DynamicArray(unique_ptr<T[]> items, int count) : DynamicArray(count) {
        if (items == nullptr) {
            throw std::out_of_range("invalid items argument for constructor");
        }
        for (int i = 0; i < count; i++) {
            elements[i] = items[i];
        }
    }

    DynamicArray(int size) : size(size), capacity(size + 1) {
        if (size < 0) {
            throw std::out_of_range("invalid size argument");
        }
        elements = make_unique<T[]>(capacity);
    }

    DynamicArray(const DynamicArray& dynamicArray)
        : size(dynamicArray.size), capacity(dynamicArray.capacity) {
        elements = make_unique<T[]>(capacity);
        for (int i = 0; i < size; i++) {
            elements[i] = dynamicArray.elements[i];
        }
    }

    DynamicArray& operator=(const DynamicArray& dynamicArray) {
        if (this == &dynamicArray) {
            return *this;
        }

        size = dynamicArray.size;
        capacity = dynamicArray.capacity;
        elements = make_unique<T[]>(capacity);
        for (int i = 0; i < size; i++) {
            elements[i] = dynamicArray.elements[i];
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
        Resize(size + 1);
        for (int i = size; i > index; i--) {
            elements[i] = elements[i - 1];
        }
        elements[index] = value;
    }

    void Resize(int newSize) {
        if (newSize < 0) {
            throw std::out_of_range("invalid newSize");
        }

        if (newSize > capacity) {
            Reserve(newSize * 2);
        } else if (newSize < size) {
            auto newElements = make_unique<T[]>(newSize);
            for (int i = 0; i < newSize; i++) {
                newElements[i] = elements[i];
            }
            elements = move(newElements);
            capacity = newSize;
        }
        size = newSize;
    }
};

#endif // DYNAMICARRAY_H
