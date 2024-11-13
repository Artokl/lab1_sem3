#ifndef SWAP_H
#define SWAP_H

#include "Move.h"

template <typename T>
inline void my_swap(T& a, T& b)
{
    T buffer = move(a);
    a = move(b);
    b = move(buffer);
}

#endif //SWAP_H
