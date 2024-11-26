#ifndef ARRAYSEQUENCETESTS_H
#define ARRAYSEQUENCETESTS_H

#include "../ArraySequence.h"
#include "assert.h"

void TestArraySequenceConstructors()
{
    int a[6] = {1, 2, 3, 4, 5, 6};

    const auto test1 = shared_ptr<MutableArraySequence<int>>(new MutableArraySequence<int>(a, 6));
    assert(test1->GetLength() == 6);
    for (int i = 0; i < test1->GetLength(); i++) {
        assert(test1->Get(i) == a[i]);
    }

    const auto test2 = shared_ptr<ImmutableArraySequence<int>>(new ImmutableArraySequence<int>(a, 6));
    assert(test2->GetLength() == 6);
    for (int i = 0; i < test2->GetLength(); i++) {
        assert(test2->Get(i) == a[i]);
    }
}

void TestArraySequenceDecompositions()
{
    int a[5] = {5, 4, 3, 2, 1};
    const auto test1 = shared_ptr<MutableArraySequence<int>>(new MutableArraySequence<int>(a, 5));

    assert(test1->GetFirst() == 5);
    assert(test1->GetLast() == 1);
    assert(test1->GetLength() == 5);
    assert(test1->Get(2) == a[2]);

    const auto test2 = test1->GetSubSequence(2, 4);
    for (int i = 0; i < test2->GetLength(); i++) {
        assert(test2->Get(i) == test1->Get(i + 2));
    }

    const auto test3 = shared_ptr<ImmutableArraySequence<int>>(new ImmutableArraySequence<int>(a, 5));
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

    const auto test = shared_ptr<MutableArraySequence<int>>(new MutableArraySequence<int>(a, 5));
    const auto test1 = shared_ptr<MutableArraySequence<int>>(new MutableArraySequence<int>(b, 3));

    const auto test2 = test->Concat(*test1);
    for (int i = 0; i < test2->GetLength(); i++) {
        assert(test2->Get(i) == c[i]);
    }

    const auto test3 = shared_ptr<ImmutableArraySequence<int>>(new ImmutableArraySequence<int>(a, 5));
    const auto test4 = shared_ptr<ImmutableArraySequence<int>>(new ImmutableArraySequence<int>(b, 3));

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
