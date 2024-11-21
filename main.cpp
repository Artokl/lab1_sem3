#include "Tests/ArraySequenceTests.h"
#include "Tests/DynamicArrayTests.h"
#include "Tests/UniquePtrTests.h"
#include "Tests/SharedPtrTests.h"
#include "Tests/WeakPtrTests.h"
int main() {
    unique_ptrTests();
    shared_ptrTests();
    weak_ptrTests();
    TestsDynamicArray();
    TestsArraySequence();
    return 0;
}
