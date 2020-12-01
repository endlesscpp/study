#include <stdio.h>
#include <string.h>

void bar(const char* str)
{
    char buf[4];
    strcpy(buf, str);
}

void foo()
{
    bar("abc");
    printf("Hello from foo!\n");
}

int main()
{
    foo();
    return 0;
}

