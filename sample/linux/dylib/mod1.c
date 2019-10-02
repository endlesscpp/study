#include <stdio.h>
#include "demo.h"
#define _GNU_SOURCE
#include <dlfcn.h>


typedef struct DL_info {
    const char* dli_fname;
    void* dli_fbase;
    const char* dli_sname;
    void* dli_saddr;
} Dl_info;

void func_mod1()
{
    printf("In func_mod1()...\n");
    struct DL_info dlinfo = {0};
    dladdr(func_mod1, &dlinfo);

    printf("so path = %s\n", dlinfo.dli_fname);

}
