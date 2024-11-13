#ifndef DELETER_H
#define DELETER_H

template <typename T>
struct DefaultDelete {
    void operator()(const T* ptr) const;
};

template <typename T>
struct DefaultDelete<T[]> {
    void operator()(const T* ptr) const;
};

template <typename T>
void DefaultDelete<T>::operator()(const T* ptr) const {
    delete ptr;
}

template <typename T>
void DefaultDelete<T[]>::operator()(const T* ptr) const {
    delete[] ptr;
}

#endif //DELETER_H
