#include <stdio.h>
#include <string.h>

void bar(const char* str)
{
    char buf[4];
    strcpy(buf, str);
}

void foo()
{
    printf("Hello from foo!\n");
}

int main(int argc, char** argv)
{
    if (argc < 2) {
        printf("./stack <str>\n");
        return 0;
    }
    bar(argv[1]);
    foo();
}

