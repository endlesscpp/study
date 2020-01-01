#include <stdio.h>
#include <stdlib.h>
#include "hello.h"

void hello()
{
    void* p = malloc(200);
    printf("hello\n");
}

