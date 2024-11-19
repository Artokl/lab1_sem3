cmake_minimum_required(VERSION 3.28)
project(lab_1)

set(CMAKE_CXX_STANDARD 23)

add_executable(lab_1 main.cpp
        Unique_Ptr.h
        Deleters.h
        Deleters.h
        Move.h
        Swap.h
        Additional_Structures.h
        Shared_Ptr.h
        Weak_Ptr.h
        Tests/UniquePtrTests.h
        Tests/SharedPtrTests.h
        Tests/WeakPtrTests.h
        DynamicArray.h
        Tests/DynamicArrayTests.h
        ArraySequence.h
)
