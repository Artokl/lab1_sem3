#ifndef weak_ptrTESTS_H
#define weak_ptrTESTS_H
#include <cassert>
#include "../Weak_Ptr.h"

void testweak_ptrCtors() {
    auto a = weak_ptr<int>();
    auto b = shared_ptr<int>(new int(9));
    auto c = weak_ptr(b);
    assert(c.use_count() == 1);
};

void testweak_ptrCopyCtor() {
    auto b = shared_ptr<int>(new int(9));
    auto c = weak_ptr(b);
    weak_ptr<int> d = c;
    assert(c.use_count() == 2);
}

void testweak_ptrMoveCtor() {
    auto b = shared_ptr<int>(new int(9));
    auto c = weak_ptr(b);
    weak_ptr<int> d = move(c);
    assert(d.use_count() == 1);
}

void testweak_ptrCopyAssignmentOperator() {
    auto b = shared_ptr<int>(new int(9));
    auto c = weak_ptr(b);
    auto d = weak_ptr<int>();
    d = c;
    assert(d.use_count() == 2);
}

void testweak_ptrMoveAssignmentOperator() {
    auto b = shared_ptr<int>(new int(9));
    auto c = weak_ptr(b);
    auto d = weak_ptr<int>();
    d = move(c);
    assert(d.use_count() == 1);
}

void testweak_ptrReset() {
    auto b = shared_ptr<int>(new int(9));
    auto c = weak_ptr(b);
    auto d = weak_ptr(b);
    d.reset();
    assert(c.use_count() == 1);
}

void testweak_ptrExpired() {
    auto a = weak_ptr<int>();
    assert(a.expired() == true);
    {
        auto b = shared_ptr<int>(new int(9));
        a = weak_ptr(b);
        assert(a.expired() == false);
    }
    assert(a.expired() == true);
}

void testweak_ptrLock() {
    auto a = shared_ptr<int>(new int(8));
    auto b = weak_ptr(a);
    auto c = b.lock();
    assert(a.use_count() == 2);
    assert(b.use_count() == 1);
}

void testweak_ptruse_count() {
    auto a = shared_ptr<int>(new int(8));
    auto b = weak_ptr(a);
    assert(b.use_count() == 1);
    auto c = b;
    assert(c.use_count() == 2);
    {
        auto d = c;
        assert(d.use_count() == 3);
    }
    assert(c.use_count() == 2);
}

void weak_ptrTests() {
    testweak_ptrCtors();
    testweak_ptrCopyCtor();
    testweak_ptrMoveCtor();
    testweak_ptrCopyAssignmentOperator();
    testweak_ptrMoveAssignmentOperator();
    testweak_ptrReset();
    testweak_ptrExpired();
    testweak_ptrLock();
    testweak_ptruse_count();
}
#endif //weak_ptrTESTS_H
