#ifndef ARRAYSEQUENCE_H
#define ARRAYSEQUENCE_H

#include <memory>
#include <stdexcept>
#include "DynamicArray.h"
#include "Shared_Ptr.h"

template <typename T>
class ArraySequence {
protected:
    shared_ptr<DynamicArray<T>> array;

public:
    ArraySequence()
        : array(new DynamicArray<T>()) {}

    explicit ArraySequence(int count)
        : array(new DynamicArray<T>(count)) {}

    ArraySequence(T* items, int count)
        : array(new DynamicArray<T>(items, count)) {}

    ArraySequence(const ArraySequence<T>& seq) = delete;

    explicit ArraySequence(const DynamicArray<T>& arr) = delete;

    virtual ~ArraySequence() = default;

    T GetFirst() const {
        return array->Get(0);
    }

    T GetLast() const {
        return array->Get(array->GetSize() - 1);
    }

    T Get(int index) const {
        return array->Get(index);
    }

    int GetLength() const {
        return array->GetSize();
    }
    
};

template <typename T>
class MutableArraySequence : public ArraySequence<T> {
private:
    shared_ptr<MutableArraySequence> GetInstance() {
        return shared_ptr<MutableArraySequence>(new MutableArraySequence());
    }

public:
    using ArraySequence<T>::ArraySequence;

    shared_ptr<MutableArraySequence> Append(T item) {
        auto result = GetInstance();
        result->array->Resize(result->array->GetSize() + 1);
        result->array->Set(item, result->array->GetSize() - 1);
        return result;
    }

    shared_ptr<MutableArraySequence> Prepend(T item) {
        auto result = GetInstance();
        result->array->Resize(result->array->GetSize() + 1);
        for (int i = result->array->GetSize() - 1; i > 0; --i) {
            result->array->Set(result->array->Get(i - 1), i);
        }
        result->array->Set(item, 0);
        return result;
    }

    shared_ptr<MutableArraySequence> InsertAt(T item, int index) {
        if (index < 0 || index > this->array->GetSize()) {
            throw std::out_of_range("Index out of range.");
        }
        auto result = GetInstance();
        result->array->Resize(result->array->GetSize() + 1);
        for (int i = result->array->GetSize() - 1; i > index; --i) {
            result->array->Set(result->array->Get(i - 1), i);
        }
        result->array->Set(item, index);
        return result;
    }

    shared_ptr<MutableArraySequence> Concat(ArraySequence<T>& list) {
        auto result = shared_ptr<MutableArraySequence>(new MutableArraySequence());
        for (int i = 0; i < this->GetLength(); i++) {
            result->Append(this->Get(i));
        }
        for (int i = 0; i < list.GetLength(); i++) {
            result->Append(list.Get(i));
        }
        return result;
    }

    shared_ptr<MutableArraySequence> GetSubSequence(int startIndex, int endIndex) {
        if (startIndex < 0 || endIndex < startIndex || endIndex >= this->array->GetSize()) {
            throw std::invalid_argument("Invalid argument");
        }
        auto result = shared_ptr<MutableArraySequence>(new MutableArraySequence());
        for (int i = startIndex; i <= endIndex; i++) {
            result->Append(this->Get(i));
        }
        return result;
    }
};

template <typename T>
class ImmutableArraySequence : public ArraySequence<T> {
private:
    shared_ptr<ImmutableArraySequence> GetInstance() {
        auto result = shared_ptr<ImmutableArraySequence>(new ImmutableArraySequence());
        for (int i = 0; i < this->GetLength(); i++) {
            result->array->Set(this->array->Get(i), i);
        }
        return result;
    }

public:
    using ArraySequence<T>::ArraySequence;

    shared_ptr<ImmutableArraySequence> Append(T item) {
        auto result = GetInstance();
        result->array->Resize(result->array->GetSize() + 1);
        result->array->Set(item, result->array->GetSize() - 1);
        return result;
    }

    shared_ptr<ImmutableArraySequence> Prepend(T item) {
        auto result = GetInstance();
        result->array->Resize(result->array->GetSize() + 1);
        for (int i = result->array->GetSize() - 1; i > 0; --i) {
            result->array->Set(result->array->Get(i - 1), i);
        }
        result->array->Set(item, 0);
        return result;
    }

    shared_ptr<ImmutableArraySequence> InsertAt(T item, int index) {
        if (index < 0 || index > this->array->GetSize()) {
            throw std::out_of_range("Index out of range.");
        }
        auto result = GetInstance();
        result->array->Resize(result->array->GetSize() + 1);
        for (int i = result->array->GetSize() - 1; i > index; --i) {
            result->array->Set(result->array->Get(i - 1), i);
        }
        result->array->Set(item, index);
        return result;
    }

    shared_ptr<ImmutableArraySequence> Concat(ArraySequence<T>& list) {
        auto mutableSequence = shared_ptr<MutableArraySequence<T>>(new MutableArraySequence<T>());
        for (int i = 0; i < this->GetLength(); i++) {
            mutableSequence->Append(this->Get(i));
        }
        for (int i = 0; i < list.GetLength(); i++) {
            mutableSequence->Append(list.Get(i));
        }

        auto result = shared_ptr<ImmutableArraySequence>(new ImmutableArraySequence());
        for (int i = 0; i < mutableSequence->GetLength(); i++) {
            result = result->Append(mutableSequence->Get(i));
        }
        return result;
    }

    shared_ptr<ImmutableArraySequence> GetSubSequence(int startIndex, int endIndex) {
        if (startIndex < 0 || endIndex < startIndex || endIndex >= this->GetLength()) {
            throw std::invalid_argument("Invalid argument");
        }

        auto mutableSequence = shared_ptr<MutableArraySequence<T>>(new MutableArraySequence<T>());
        for (int i = startIndex; i <= endIndex; i++) {
            mutableSequence->Append(this->Get(i));
        }

        auto result = shared_ptr<ImmutableArraySequence>(new ImmutableArraySequence());
        for (int i = 0; i < mutableSequence->GetLength(); i++) {
            result = result->Append(mutableSequence->Get(i));
        }
        return result;
    }
};

#endif // ARRAYSEQUENCE_H
