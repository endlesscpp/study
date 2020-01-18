#include "test.h"
#include <stdlib.h>
#include <stdio.h>

#if 0
void commonFunc() {
    printf("in commonFunc\n");
}
#endif


void bar() {
    commonFunc();
    Common::func();
}
