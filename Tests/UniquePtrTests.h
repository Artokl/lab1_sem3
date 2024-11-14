#ifndef ALLTESTS_H
#define ALLTESTS_H

#include <cassert>
#include "../Unique_Ptr.h"

void testunique_ptrCtors() {
    const unique_ptr<int> a;
    assert(a == nullptr);
    const auto b = unique_ptr<double>(new double(8.0));
    assert(*b == 8.0);
}

void testunique_ptrMoveCtor() {
    auto a = unique_ptr<int>(new int(8));
    const auto b = unique_ptr(move(a));
    assert(a == nullptr);
    assert(*b == 8);
}

void testunique_ptrMoveAssignmentOperator() {
    auto a = unique_ptr<int>(new int(8));
    auto b = unique_ptr<int>(new int(9));
    b = move(a);
    assert(*b == 8);
    assert(a == nullptr);
}

void testunique_ptrIndirectionOperator() {
    const auto a = unique_ptr<float>(new float(46.0f));
    assert(*a == 46.0f);
}

void testunique_ptrDereferenceOperator() {
    struct A {int a = 8;};
    const auto b = unique_ptr<A>(new A);
    assert(b->a == 8);
}

void testunique_ptrSubscriptOperator() {
    const auto array = new int[10];
    for (int i = 0; i < 10; i++) {
        array[i] = i * 2;
    }
    const auto a = unique_ptr<int[]>(array);
    for (int i = 0; i < 10; i++) {
        assert(a[i] == array[i]);
    }
}

void testunique_ptrReset() {
    auto a = unique_ptr<int>(new int(8));
    a.reset();
    assert(a.isNull());
}

void testunique_ptrRelease() {
    auto a = unique_ptr<int>(new int(8));
    const int* b = a.release();
    assert(a == nullptr);
    assert(*b == 8);
}

void testunique_ptrCompareOperators() {
    const auto a = unique_ptr<int>(new int(8));
    const auto b = unique_ptr<int>(new int(9));
    const auto c = unique_ptr<int>();
    assert((a == a) == true);
    assert((a != a) == false);
    assert((a == b) == false);
    assert((a != b) == true);
    assert((c == nullptr) == true);
    assert((a == nullptr) == false);
    assert((nullptr != a) == true);
}

void testMakeUnique() {
    const auto a = make_unique<int>(8);
    assert(*a == 8);
    const auto b = make_unique<int[]>(2);
    b[0] = 2;
    b[1] = 4;
}

void unique_ptrTests() {
    testunique_ptrCtors();
    testunique_ptrMoveCtor();
    testunique_ptrMoveAssignmentOperator();
    testunique_ptrIndirectionOperator();
    testunique_ptrDereferenceOperator();
    testunique_ptrSubscriptOperator();
    testunique_ptrReset();
    testunique_ptrRelease();
    testunique_ptrCompareOperators();
    testMakeUnique();
}

#endif //ALLTESTS_H
