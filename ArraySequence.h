#ifndef ARRAYSEQUENCE_H
#define ARRAYSEQUENCE_H

#include <memory>
#include <stdexcept>
#include "DynamicArray.h"
#include "Shared_Ptr.h"

template <typename T> class Sequence {
public:
    virtual ~Sequence () {}
    virtual T GetFirst () const = 0;
    virtual T GetLast () const = 0;
    virtual T Get (int index) = 0;
    virtual int GetLength () = 0;

    virtual shared_ptr<Sequence> GetSubSequence (int startIndex, int endIndex) = 0;
    virtual shared_ptr<Sequence> Append (T item) = 0;
    virtual shared_ptr<Sequence> Prepend (T item) = 0;
    virtual shared_ptr<Sequence> InsertAt (T item, int index) = 0;
    virtual shared_ptr<Sequence> Concat (Sequence &list) = 0;
};
template <typename T>
class ArraySequence: public Sequence<T>{
protected:
    shared_ptr<DynamicArray<T>> array;

    virtual shared_ptr<ArraySequence> GetInstance() = 0;

public:
    ArraySequence()
        : array(make_shared<DynamicArray<T>>()) {}

    explicit ArraySequence(int count)
        : array(make_shared<DynamicArray<T>>(count)) {}

    ArraySequence(T* items, int count)
        : array(make_shared<DynamicArray<T>>(items, count)) {}

    ArraySequence(const ArraySequence<T>& seq)
        : array(make_shared<DynamicArray<T>>(*seq.array)) {}

    explicit ArraySequence(const DynamicArray<T>& arr)
        : array(make_shared<DynamicArray<T>>(arr)) {}

    ~ArraySequence() override = default;

    T GetFirst() const override {
        return array->Get(0);
    }

    T GetLast() const override {
        return array->Get(array->GetSize() - 1);
    }

    T Get(int index) override {
        return array->Get(index);
    }

    int GetLength() override {
        return array->GetSize();
    }

    shared_ptr<ArraySequence> Append(T item) override {
        auto result = GetInstance();
        result->array->Set(item, result->array->GetSize());
        return result;
    }

    shared_ptr<ArraySequence> Prepend(T item) override {
        auto result = GetInstance();
        result->array->Set(item, 0);
        return result;
    }

    shared_ptr<ArraySequence> InsertAt(T item, int index) override {
        auto result = GetInstance();
        result->array->Set(item, index);
        return result;
    }
};

template <typename T>
class MutableArraySequence : public ArraySequence<T> {
private:
    shared_ptr<ArraySequence<T>> GetInstance() override {
        return make_shared<MutableArraySequence>();
    }

public:
    using ArraySequence<T>::ArraySequence;

    shared_ptr<MutableArraySequence> Concat(Sequence<T>& list) override {
        auto result = make_shared<MutableArraySequence>();
        for (int i = 0; i < this->GetLength(); i++) {
            result->Append(this->Get(i));
        }
        for (int i = 0; i < list.GetLength(); i++) {
            result->Append(list.Get(i));
        }
        return result;
    }

    shared_ptr<MutableArraySequence> GetSubSequence(int startIndex, const int endIndex) override {
        if (startIndex < 0 || endIndex < 0 || startIndex >= this->array->GetSize() || endIndex < startIndex) {
            throw std::invalid_argument("Invalid argument");
        }

        auto result = make_shared<MutableArraySequence<T>>();
        for (int i = startIndex; i <= endIndex; i++) {
            result->Append(this->Get(i));
        }
        return result;
    }
};

template <typename T>
class ImmutableArraySequence : public ArraySequence<T> {
private:
    shared_ptr<ArraySequence<T>> GetInstance() override {
        auto result = make_shared<ImmutableArraySequence>();
        for (int i = 0; i < this->GetLength(); i++) {
            result->array->Set(this->array->Get(i), i);
        }
        return result;
    }

public:
    using ArraySequence<T>::ArraySequence;

    shared_ptr<ImmutableArraySequence> Concat(Sequence<T>& list) override {
        auto mutableSequence = make_shared<MutableArraySequence<T>>();
        for (int i = 0; i < this->GetLength(); i++) {
            mutableSequence->Append(this->Get(i));
        }
        for (int i = 0; i < list.GetLength(); i++) {
            mutableSequence->Append(list.Get(i));
        }

        auto result = make_shared<ImmutableArraySequence>();
        for (int i = 0; i < mutableSequence->GetLength(); i++) {
            result = result->Append(mutableSequence->Get(i));
        }
        return result;
    }

    shared_ptr<ImmutableArraySequence> GetSubSequence(const int startIndex, int endIndex) override {
        if (startIndex < 0 || endIndex < startIndex || endIndex >= this->GetLength()) {
            throw std::invalid_argument("Invalid argument");
        }

        auto mutableSequence = make_shared<MutableArraySequence<T>>();
        for (int i = startIndex; i <= endIndex; i++) {
            mutableSequence->Append(this->Get(i));
        }

        auto result = make_shared<ImmutableArraySequence>();
        for (int i = 0; i < mutableSequence->GetLength(); i++) {
            result = result->Append(mutableSequence->Get(i));
        }
        return result;
    }
};

#endif //ARRAYSEQUENCE_H
