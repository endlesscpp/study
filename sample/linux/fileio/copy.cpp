#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

int main(int argc, char** argv) {
    if (argc != 3 || strcmp(argv[1], "--help") == 0) {
        printf("%s old-file new-file\n", argv[0]);
        return -1;
    }

    int inputFd = open(argv[1], O_RDONLY);
    if (inputFd == -1) {
        printf("failed to open file %s\n", argv[1]);
        return -1;
    }

    int    openFlags = O_CREAT | O_WRONLY | O_TRUNC;
    mode_t filePerms
        = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
    int outputFd = open(argv[2], openFlags, filePerms);
    if (outputFd == -1) {
        printf("failed to open file %s\n", argv[2]);
        return -1;
    }

    off_t pos = lseek(inputFd, 0, SEEK_END);
    if (pos != -1) {
        printf("seek end, pos = %d\n", (int)pos);
    }

    ssize_t numRead = 0;
    char    buf[BUF_SIZE];
    while (true) {
        numRead = read(inputFd, buf, sizeof(buf));
        if (numRead == 0) {
            break;
        }

        if (numRead < 0) {
            printf("read failed, rc = %d\n", errno);
            return -1;
        }

        if (numRead != write(outputFd, buf, numRead)) {
            printf("could NOT write whole buffer\n");
            return -1;
        }
    }

    if (close(inputFd) == -1) {
        printf("close input failed, rc = %d\n", errno);
        return -1;
    }

    if (close(outputFd) == -1) {
        printf("close output failed, rc = %d\n", errno);
        return -1;
    }

    return 0;
}

