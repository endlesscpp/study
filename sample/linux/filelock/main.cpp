#include <iostream>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <inttypes.h>

static int lockRegion(int fd, int cmd, short type, int offset, int len) {
    struct flock lock = {0};
    lock.l_type = type;
    lock.l_whence = SEEK_SET;
    lock.l_start = offset;
    lock.l_len = len;
    lock.l_pid = 0;

    return fcntl(fd, cmd, &lock);
}

static int wlock(int fd, int offset, int len) {
    return lockRegion(fd, F_SETLK, F_WRLCK, offset, len);
}

static int unlock(int fd, int offset, int len) {

    int ret = lockRegion(fd, F_SETLK, F_UNLCK, offset, len);
    if (ret == -1) {
        printf("unlock failed, begin offset = %d, rc = %d\n", offset, errno);
        return -1;
    }

    return 0;
}

//static __thread int tlsLockOffset = -1;  // -1 means not locked
static thread_local int tlsLockOffset = -1;  // -1 means not locked

static void testLock(int offset) {
    if (tlsLockOffset != -1) {
        printf("already has lock, offset = %d\n", tlsLockOffset);
        return;
    }

    if (-1 == mkdir("/var/lock/oak", 0755)) {
        if (errno != EEXIST) {
            perror("mkdir failed");
            return;
        }
    }

    int fd = open("/var/lock/oak/sync.lock", O_CREAT | O_RDWR, 0644);
    if (fd == -1) {
        perror("open lock file");
        return;
    }

    int ret = wlock(fd, offset, 1);
    if (ret == -1) {
        perror("wlock");
        printf("wlock failed, offset = %d, ret = %d\n", offset, ret);
        return;
    }

    ret = wlock(fd, offset, 1);
    if (ret == -1) {
        perror("wlock2");
        printf("wlock failed, offset = %d, ret = %d\n", offset, ret);
        return;
    }


    tlsLockOffset = offset;

    printf("press any key to exit...\n");
    getchar();
//    printf("tlsLockOffset2 = %d, thread = %ld\n", tlsLockOffset, (long)pthread_self());

    ret = unlock(fd, offset, 1);
    tlsLockOffset = -1;
    return;
}



static void* threadEntry(void* args) {
    int offset = (int)(intptr_t)args;
    testLock(offset);
    return nullptr;
}

int main() {
    pthread_t thread1, thread2;
    pthread_create(&thread1, nullptr, threadEntry, (void*)1);
//    sleep(4);
    pthread_create(&thread2, nullptr, threadEntry, (void*)1);

    pthread_join(thread1, nullptr);
    pthread_join(thread2, nullptr);
    return 0;
}