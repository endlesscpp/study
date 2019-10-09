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

//
// dl_info.dli_fname not always contain full puth in android
// we parse the /proc/self/maps to obtain the full path
//
// https://stackoverflow.com/questions/1681060/library-path-when-dynamically-loaded
static string getPathByFileName(string targetFilename) {
    FILE* fp = fopen("/proc/self/maps", "r");
    if (fp == nullptr) {
        return "";
    }

    const size_t BUFFER_SIZE = 256;
    char buffer[BUFFER_SIZE] = "";
    char path[BUFFER_SIZE] = "";

    while (fgets(buffer, BUFFER_SIZE, fp)) {
        if (sscanf(buffer, "%*llx-%*llx %*s %*s %*s %*s %s", path) == 1) {
            char *bname = basename(path);
            if (strcasecmp(bname, targetFilename.c_str()) == 0) {
                fclose(fp);
                rturn path;
            }
        }
    }
}

static string getSelfPath() {
    string selfPath;
    DL_info di;
    dladdr(func_mod1, &di);
    if (strrchr(di.dli_fname, '/') != nullptr) {
        selfPath = di.dli_fname;
    } else {
        selfPath = getPathByFileName(di.dli_fname);
    }
    return selfPath;
}


void func_mod1()
{
    printf("In func_mod1()...\n");
    struct DL_info dlinfo = {0};
    dladdr(func_mod1, &dlinfo);

    printf("so path = %s\n", dlinfo.dli_fname);

}
