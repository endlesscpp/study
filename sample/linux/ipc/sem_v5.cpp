//
// Created by Dengfeng on 2019/10/1.
//
#include "sem_v5.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include "semun.h"
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <cerrno>

static int getInt(char* p, int defValue) {
    if (p == nullptr || strlen(p) == 0) {
        return defValue;
    }

    int val = atoi(p);
    return val;
}

static void semDestroy(int semid) {
    semctl(semid, 0,IPC_RMID);
}

//
// sem wait. 0 means success, otherwise fail
//
static int semWait(int semid) {
    struct sembuf sop;
    sop.sem_num = 0;    // operate on semaphore 0
    sop.sem_op = 0;     // wait for value to equal 0
    sop.sem_flg = 0;    // has IPC_NOWAIT or SEM_UNDO flags
    if (semop(semid, &sop, 1) == -1) {
        perror("semWait");
        return -1;
    }
    return 0;
}

static int semRelease(int semid) {
    struct sembuf sop;
    sop.sem_num = 0;            // operate on semaphore 0
    sop.sem_op = -1;            // decrement by 1
    sop.sem_flg = SEM_UNDO;     // has IPC_NOWAIT or SEM_UNDO flags
    if (semop(semid, &sop, 1) == -1) {
        // attention here. error == EINTR
        perror("semWait");
        return -1;
    }
    return 0;
}
//
// demostrate how to initialize the semaphore correctly
// return -1 means fail, others return the semid.
//
static int semInit(int key, int perm) {
    int semid = semget(key, 1, perm | IPC_CREAT | IPC_EXCL);
    if (semid != -1) {
        union semun arg;
        arg.val = 0;
        if (-1 == semctl(semid, 0, SETVAL, arg)) {
            perror("semctl to 0");
            return -1;
        }

        // perform a no-op semaphore operation - change sem_otime so
        // other process can see we have initialized the semaphore
        struct sembuf sop;
        sop.sem_num = 0;    // operate on semaphore 0
        sop.sem_op = 0;     // wait for value to equal 0
        sop.sem_flg = 0;    // has IPC_NOWAIT or SEM_UNDO flags
        if (semop(semid, &sop, 1) == -1) {
            perror("semop with no-op");
            semDestroy(semid);
            return -1;
        }
        return semid;
    } else {
        const int MAX_TRIES = 10;
        if (errno != EEXIST) {
            // unexpected error from semget
            perror("semget");
            return -1;
        }

        semid = semget(key, 1, perm);
        if (semid == -1) {
            perror("semget existing semaphore");
            return -1;
        }

        // wait until other process call semop
        union semun arg;
        struct semid_ds ds;
        arg.buf = &ds;
        for (int i = 0; i < MAX_TRIES; i++) {
            if (semctl(semid, 0, IPC_STAT, arg) == -1) {
                perror("semctl");
                return -1;
            }
            if (ds.sem_otime != 0) {
                // other semop performed
                break;
            }
            sleep(1);
        }

        if (ds.sem_otime == 0) {
            printf("existing semaphore not initialized");
            semDestroy(semid);
            return -1;
        }

        return semid;
    }
}

void test_sem_v5(int argc, char** argv) {
    if (argc == 2) {
        //int semid = semget(IPC_PRIVATE, 1, IPC_CREAT | 0644);
        int semid = semget(123, 1, IPC_CREAT | 0644);
        if (semid == -1) {
            perror("semget");
            return;
        }

        union semun arg;
        arg.val = getInt(argv[1], 0);

        if (-1 == semctl(semid, 0, SETVAL, arg)) {
            perror("semctl");
            return;
        }

        printf("semphore ID = %d\n", semid);
    } else {
        struct sembuf sop;
        int semid = getInt(argv[1], 0);

        sop.sem_num = 0;
        sop.sem_op = getInt(argv[2], 0);    // add, substract or wait till 0
        sop.sem_flg = 0;

        printf("%ld: about to sem at %s\n", (long)getpid(), "");
        if (semop(semid, &sop,1) == -1) {
            perror("semop");
            return;
        }
        printf("%ld: semop completed at %s\n", (long)getpid(), "");
    }
}

