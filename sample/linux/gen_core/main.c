#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>

#define CORE_SIZE 1024 * 1024 * 5

int main() {
    struct rlimit lmt;
    if (getrlimit(RLIMIT_CORE, &lmt) == -1) {
        return -1;
    }

    printf("before set rlimit, rlimit.curr = %d, max = %d\n",
           (int)lmt.rlim_cur, (int)lmt.rlim_max);

    lmt.rlim_cur = (rlim_t)CORE_SIZE;
    lmt.rlim_max = (rlim_t)CORE_SIZE;

    if (setrlimit(RLIMIT_CORE, &lmt) == -1) {
        return -1;
    }

    if (getrlimit(RLIMIT_CORE, &lmt) == -1) {
        return -1;
    }

    printf("after set rlimit, rlimit.curr = %d, max = %d\n",
           (int)lmt.rlim_cur, (int)lmt.rlim_max);

    int* ptr = NULL;
    *ptr = 10;

    return 0;
}