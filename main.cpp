#include <iostream>
#include "Tests/UniquePtrTests.h"
#include "Tests/SharedPtrTests.h"
#include "Tests/WeakPtrTests.h"
int main() {
    unique_ptrTests();
    shared_ptrTests();
    weak_ptrTests();
    return 0;
}
