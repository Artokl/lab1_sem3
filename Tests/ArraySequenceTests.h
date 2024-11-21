#ifndef ARRAYSEQUENCETESTS_H
#define ARRAYSEQUENCETESTS_H

#include "../ArraySequence.h"
#include "assert.h"

void TestArraySequenceConstructors()
{
    int a[6] = {1, 2, 3, 4, 5, 6};

    const auto test1 = make_shared<MutableArraySequence<int>>(a, 6);
    assert(test1->GetLength() == 6);
    for (int i = 0; i < test1->GetLength(); i++) {
        assert(test1->Get(i) == a[i]);
    }

    const auto test2 = make_shared<ImmutableArraySequence<int>>(a, 6);
    assert(test2->GetLength() == 6);
    for (int i = 0; i < test2->GetLength(); i++) {
        assert(test2->Get(i) == a[i]);
    }

    const auto test3 = make_shared<MutableArraySequence<int>>(*test1);
    const auto test4 = make_shared<ImmutableArraySequence<int>>(*test2);

    assert(test3->GetLength() == 6);
    assert(test4->GetLength() == 6);
    for (int i = 0; i < test3->GetLength(); i++) {
        assert(test3->Get(i) == a[i]);
        assert(test4->Get(i) == a[i]);
    }

    const DynamicArray<int> testAr1(a, 6);
    const DynamicArray<int> testAr2(a, 6);

    const auto test5 = make_shared<MutableArraySequence<int>>(testAr1);
    const auto test6 = make_shared<ImmutableArraySequence<int>>(testAr2);

    assert(test5->GetLength() == testAr1.GetSize());
    assert(test6->GetLength() == testAr2.GetSize());
    for (int i = 0; i < test5->GetLength(); i++) {
        assert(test5->Get(i) == testAr1.Get(i));
        assert(test6->Get(i) == testAr2.Get(i));
    }
}

void TestArraySequenceDecompositions()
{
    int a[5] = {5, 4, 3, 2, 1};
    const auto test1 = make_shared<MutableArraySequence<int>>(a, 5);

    assert(test1->GetFirst() == 5);
    assert(test1->GetLast() == 1);
    assert(test1->GetLength() == 5);
    assert(test1->Get(2) == a[2]);

    const auto test2 = test1->GetSubSequence(2, 4);
    for (int i = 0; i < test2->GetLength(); i++) {
        assert(test2->Get(i) == test1->Get(i + 2));
    }

    const auto test3 = make_shared<ImmutableArraySequence<int>>(a, 5);
    assert(test3->GetFirst() == 5);
    assert(test3->GetLast() == 1);
    assert(test3->GetLength() == 5);
    assert(test3->Get(2) == a[2]);

    const auto test4 = test3->GetSubSequence(2, 4);
    for (int i = 0; i < test4->GetLength(); i++) {
        assert(test4->Get(i) == test3->Get(i + 2));
    }
}

void TestArraySequenceOperations()
{
    int a[5] = {5, 4, 3, 2, 1};
    int b[3] = {8, 9, 10};
    const int c[] = {5, 4, 3, 2, 1, 8, 9, 10};

    auto test = make_shared<MutableArraySequence<int> >(a, 5);
    const auto test1 = make_shared<MutableArraySequence<int>>(b, 3);

    const auto test2 = test->Concat(*test1);
    for (int i = 0; i < test2->GetLength(); i++) {
        assert(test2->Get(i) == c[i]);
    }

    test = test->Append(6);
    assert(test->GetLast() == 6);

    test = test->Prepend(7);
    assert(test->GetFirst() == 7);

    test = test->InsertAt(8, 3);
    assert(test->Get(3) == 8);

    const auto test3 = make_shared<ImmutableArraySequence<int>>(a, 5);
    const auto test4 = make_shared<ImmutableArraySequence<int>>(b, 3);

    const auto test5 = test3->Concat(*test4);
    for (int i = 0; i < test5->GetLength(); i++) {
        assert(test5->Get(i) == c[i]);
    }
}

void TestsArraySequence()
{
    TestArraySequenceConstructors();
    TestArraySequenceDecompositions();
    TestArraySequenceOperations();
}

#endif // ARRAYSEQUENCETESTS_H
