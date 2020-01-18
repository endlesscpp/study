#include "test.h"
#include <stdlib.h>
#include <stdio.h>

// if both foo / bar.cpp inclues commonFunc. compile error.
#if 0
void commonFunc() {
    printf("in commonFunc\n");
}
#endif


void foo() {
    commonFunc();
    Common::func();
}
