#ifndef DELETER_H
#define DELETER_H

template <typename T>
struct DefaultDelete {
    void operator()(const T* ptr) {
        delete ptr;
    }
};

template <typename T>
struct DefaultDelete<T[]> {
    void operator()(const T* ptr) {
        delete[] ptr;
    }
};

#endif // DELETER_H
