#include <iostream>
#include "Tests/UniquePtrTests.h"
#include "Tests/SharedPtrTests.h"
#include "Tests/WeakPtrTests.h"
#include "Tests/DynamicArrayTests.h"
int main() {
    unique_ptrTests();
    shared_ptrTests();
    weak_ptrTests();
    TestsDynamicArray();
    return 0;
}
