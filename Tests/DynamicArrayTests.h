#ifndef DINAMICARRAYTESTS_H
#define DINAMICARRAYTESTS_H

#include "../DynamicArray.h"
#include "assert.h"

void TestDynamicArrayConstructors()
{
    const auto a = new int[5];
    a[0] = 5;
    a[1] = 4;
    a[2] = 3;
    a[3] = 2;
    a[4] = 1;
    const DynamicArray<int> test1(5);
    assert(test1.GetSize() == 5);
    const DynamicArray test2(a, 5);
    assert(test2.GetSize() == 5);
    for (int i = 0; i < test2.GetSize(); i++)
    {
        assert(test2.Get(i) == a[i]);
    }
}
void TestDynamicArrayDecompositions()
{
    const auto a = new int[5];
    a[0] = 5;
    a[1] = 4;
    a[2] = 3;
    a[3] = 2;
    a[4] = 1;
    DynamicArray test(a, 5);
    assert(test.Get(2) == a[2]);
    assert(test.GetSize() == 5);
}
void TestDynamicArrayOperations()
{
    const auto a = new int[5];
    a[0] = 5;
    a[1] = 4;
    a[2] = 3;
    a[3] = 2;
    a[4] = 1;
    DynamicArray test(a, 5);
    assert(test.GetSize() == 5);
    for (int i = 0; i < test.GetSize(); i++)
    {
        assert(test.Get(i) == a[i]);
    }
    test.Set(6, 3);
    assert(test.Get(3) == 6);
    test.Resize(7);
    assert(test.GetSize() == 7);
}
void TestsDynamicArray()
{
    TestDynamicArrayConstructors();
    TestDynamicArrayDecompositions();
    TestDynamicArrayOperations();
}




#endif //DINAMICARRAYTESTS_H
