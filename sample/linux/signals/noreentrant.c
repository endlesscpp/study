//
// call a non-reentrant function from both main and a signal handler
//
#define _XOPEN_SOURCE 600

#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

static char* str2;  // set from argv[2]
static int handled = 0; // counts number of calls to handler

static void handler(int sig) {
    crypt(str2, "xx");
    handled++;
}


int main(int argc, char** argv) {
    if (argc != 3) {
        printf("%s str1 str2\n", argv[0]);
        return -1;
    }

    str2 = argv[2];
    char* cr1 = strdup(crypt(argv[1], "xx")); // copy statically allocated string to another buffer

    if (cr1 == NULL) {
        printf("strdup error\n");
        return -1;
    }

    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags   = 0;
    sa.sa_handler = handler;
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        printf("sigaction failed\n");
        return -1;
    }

    for (int callNum = 1, mismatch = 0;; callNum++) {
        if (strcmp(crypt(argv[1], "xx"), cr1) != 0) {
            mismatch++;
            printf("Mismatch on call %d (mismatch = %d, handled = %d)\n",
                   callNum, mismatch, handled);
        }
    }

    return 0;
}

