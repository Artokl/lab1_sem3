#ifndef MOVE_H
#define MOVE_H

template <typename T>
inline T&& move(T& in)
{
    return static_cast<T&&>(in);
}

template<typename T>
inline T&& move(T&& in)
{
    return static_cast<T&&>(in);
}

#endif //MOVE_H
