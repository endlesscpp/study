#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define STR_SIZE sizeof("rwxrwxrwx")

#define FP_SPECIAL                                     \
    1 /* Include set-user-ID, set-group-ID, and sticky \
         bit information in returned string */

char* /* Return ls(1)-style string for file permissions mask */
filePermStr(mode_t perm, int flags)
{
    static char str[STR_SIZE];

    /* If FP_SPECIAL was specified, we emulate the trickery of ls(1) in
       returning set-user-ID, set-group-ID, and sticky bit information in
       the user/group/other execute fields. This is made more complex by
       the fact that the case of the character displayed for this bits
       depends on whether the corresponding execute bit is on or off. */

    snprintf(str, STR_SIZE, "%c%c%c%c%c%c%c%c%c", (perm & S_IRUSR) ? 'r' : '-',
             (perm & S_IWUSR) ? 'w' : '-',
             (perm & S_IXUSR)
                 ? (((perm & S_ISUID) && (flags & FP_SPECIAL)) ? 's' : 'x')
                 : (((perm & S_ISUID) && (flags & FP_SPECIAL)) ? 'S' : '-'),

             (perm & S_IRGRP) ? 'r' : '-', (perm & S_IWGRP) ? 'w' : '-',
             (perm & S_IXGRP)
                 ? (((perm & S_ISGID) && (flags & FP_SPECIAL)) ? 's' : 'x')
                 : (((perm & S_ISGID) && (flags & FP_SPECIAL)) ? 'S' : '-'),

             (perm & S_IROTH) ? 'r' : '-', (perm & S_IWOTH) ? 'w' : '-',
             (perm & S_IXOTH)
                 ? (((perm & S_ISVTX) && (flags & FP_SPECIAL)) ? 't' : 'x')
                 : (((perm & S_ISVTX) && (flags & FP_SPECIAL)) ? 'T' : '-'));

    return str;
}

static void displayStat(const struct stat* p)
{
    printf("File type: ");
    switch (p->st_mode & S_IFMT) {
    case S_IFREG:
        printf("regular file\n");
        break;
    case S_IFDIR:
        printf("directory\n");
        break;
    case S_IFCHR:
        printf("character device\n");
        break;
    case S_IFBLK:
        printf("block device\n");
        break;
    case S_IFLNK:
        printf("symbol link\n");
        break;
    case S_IFIFO:
        printf("symbol link\n");
        break;
    case S_IFSOCK:
        printf("socket\n");
        break;
    default:
        break;
    }

    printf("device:         major = %ld, minor = %ld\n", (long)major(p->st_dev),
           (long)minor(p->st_dev));
    printf("inode number:   %ld\n", (long)p->st_ino);
    printf("mode:           %lo (%s)\n", (unsigned long)p->st_mode,
           filePermStr(p->st_mode, 0));
    if (p->st_mode & (S_ISUID | S_ISGID | S_ISVTX))
        printf(" special bits set: %s%s%s\n",
               (p->st_mode & S_ISUID) ? "set-UID " : "",
               (p->st_mode & S_ISGID) ? "set-GID " : "",
               (p->st_mode & S_ISVTX) ? "sticky " : "");
    printf("Number of (hard) links: %ld\n", (long)p->st_nlink);
    printf("Ownership: UID=%ld GID=%ld\n", (long)p->st_uid, (long)p->st_gid);
    if (S_ISCHR(p->st_mode) || S_ISBLK(p->st_mode))
        printf("Device number (st_rdev): major=%ld; minor=%ld\n",
               (long)major(p->st_rdev), (long)minor(p->st_rdev));

    printf("File size: %lld bytes\n", (long long)p->st_size);
    printf("Optimal I/O block size: %ld bytes\n", (long)p->st_blksize);
    printf("512B blocks allocated: %lld\n", (long long)p->st_blocks);

    printf("Last file access: %s", ctime(&p->st_atime));
    printf("Last file modification: %s", ctime(&p->st_mtime));
    printf("Last status change: %s", ctime(&p->st_ctime));
}

int main(int argc, char** argv)
{
    struct stat st       = {};
    bool        statLink = false; // true if '-l' is specified (use lstat)
    char*       filename = NULL;

    statLink = (argc > 1) && strcmp(argv[1], "-l") == 0;

    bool showUsage = false;
    if (argc > 1 && strcmp(argv[1], "--help") == 0) {
        showUsage = true;
    } else if (statLink) {
        showUsage = (argc < 3);
    } else {
        showUsage = (argc < 2);
    }

    if (showUsage) {
        printf("%s [-l] file\n"
               "   -l = use lstat() instead of stat()\n",
               argv[0]);
        return -1;
    }

    filename = statLink ? argv[2] : argv[1];

    int rc = 0;
    if (statLink) {
        rc = lstat(filename, &st);
    } else {
        rc = stat(filename, &st);
    }

    if (rc == -1) {
        printf("get file stat failed, rc = %d\n", errno);
        return rc;
    }

    displayStat(&st);
    return rc;
}
