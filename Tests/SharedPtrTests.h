#ifndef shared_ptrTESTS_H
#define shared_ptrTESTS_H

#include "../Weak_Ptr.h"
#include <cassert>
#include "../Shared_Ptr.h"

void testshared_ptrCtors() {
    auto a = shared_ptr<int>();
    assert(a == nullptr);
    auto b = shared_ptr<int>(new int(8));
    assert(*b == 8);
    auto c = weak_ptr<int>(b);
    auto d = shared_ptr<int>(c);
    assert(*d == 8);
}

void testshared_ptrCopyCtor() {
    auto a = shared_ptr<int>(new int(8));
    auto b = shared_ptr<int>(a);
    assert(b.use_count() == 2);
    assert(*b == *a);
}

void testshared_ptrMoveCtor() {
    auto a = shared_ptr<int>(new int(8));
    auto b = shared_ptr<int>(move(a));
    assert(b.use_count() == 1);
    assert(a == nullptr);
}

void testshared_ptrCopyAssignmentOperator() {
    int *ptr = new int(8);
    auto a = shared_ptr<int>(ptr);
    auto b = shared_ptr<int>(new int(9));
    auto c = shared_ptr<int>(new int(10));
    a = b;
    assert(b.use_count() == 2);
    assert(c.use_count() == 1);
    assert(*a == 9);
}

void testshared_ptrMoveAssignmentOperator() {
    int *ptr = new int(8);
    auto a = shared_ptr<int>(ptr);
    auto b = shared_ptr<int>(new int(9));
    auto c = shared_ptr<int>(new int(10));
    a = move(b);
    assert(a.use_count() == 1);
    assert(c.use_count() == 1);
    assert(*a == 9);
}

void testshared_ptrIndirectionOperator() {
    auto* ptr = new double(8.0);
    auto a = shared_ptr<double>(ptr);
    assert(*a == 8.0);
}

void testshared_ptrDereferenceOperator() {
    struct A {
        int b = 8;
    };
    auto a = shared_ptr<A>(new A);
    assert(a->b == 8);
}

void testshared_ptrSubscriptOperator() {
    const auto array = new int[10];
    for (int i = 0; i < 10; i++) {
        array[i] = i * 2;
    }
    const auto a = shared_ptr<int[]>(array);
    for (int i = 0; i < 10; i++) {
        assert(a[i] == array[i]);
    }
}

void testshared_ptrReset() {
    int* ptr = new int(8);
    auto a = shared_ptr<int>(ptr);
    shared_ptr<int> b = a;
    shared_ptr<int> c = a;
    assert(a.use_count() == 3);
    b.reset();
    assert(a.use_count() == 2);
    assert(b == nullptr);
    int* ptr2 = new int(9);
    c.reset(ptr2);
    assert(a.use_count() == 1);
    assert(*c == 9);
}

void testshared_ptruse_count() {
    const auto a = shared_ptr<int>(new int(9));
    assert(a.use_count() == 1);
    shared_ptr<int> b = a;
    assert(b.use_count() == 2);
    {
        shared_ptr<int> c = b;
        assert(c.use_count() == 3);
    }
    assert(b.use_count() == 2);
}

void testshared_ptrunique() {
    const auto a = shared_ptr<int>(new int(4));
    assert(a.unique() == true);
    shared_ptr<int> b = a;
    assert(a.unique() == false);
}

void testshared_ptrCompareOperators() {
    const auto a = shared_ptr<int>(new int(8));
    const auto b = shared_ptr<int>(new int(9));
    const auto c = shared_ptr<int>();
    assert((a == a) == true);
    assert((a != a) == false);
    assert((a == b) == false);
    assert((a != b) == true);
    assert((c == nullptr) == true);
    assert((a == nullptr) == false);
    assert((nullptr != a) == true);
}

void testMakeShared() {
    const auto a = make_shared<int>(8);
    assert(*a == 8);
    const auto b = make_shared<int[]>(2);
    b[0] = 2;
    b[1] = 4;
}

void shared_ptrTests() {
    testshared_ptrCtors();
    testshared_ptrCopyCtor();
    testshared_ptrMoveCtor();
    testshared_ptrCopyAssignmentOperator();
    testshared_ptrMoveAssignmentOperator();
    testshared_ptrIndirectionOperator();
    testshared_ptrDereferenceOperator();
    testshared_ptrSubscriptOperator();
    testshared_ptrReset();
    testshared_ptruse_count();
    testshared_ptrunique();
    testshared_ptrCompareOperators();
    testMakeShared();
};

#endif //shared_ptrTESTS_H
