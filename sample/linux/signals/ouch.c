#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void sigHandler(int sig) {
    // print the sig description
    psignal(sig, "Recv sig");

    printf("Ouch!\n");
    // use this to exit the process
    exit(-1);
}

int main(int argc, char** argv)
{
    if (signal(SIGINT, sigHandler) == SIG_ERR) {
        printf("set signal handler failed, rc = %d\n", errno);
        return -1;
    }

    for (int i = 0; ;i++) {
        printf("%d\n", i);
        sleep(3);
    }

    return 0;
}
