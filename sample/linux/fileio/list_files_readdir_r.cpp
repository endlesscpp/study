/*************************************************************************\
*                  Copyright (C) Michael Kerrisk, 2019.                   *
*                                                                         *
* This program is free software. You may use, modify, and redistribute it *
* under the terms of the GNU General Public License as published by the   *
* Free Software Foundation, either version 3 or (at your option) any      *
* later version. This program is distributed without any warranty.  See   *
* the file COPYING.gpl-v3 for details.                                    *
\*************************************************************************/

/* Solution for Exercise 18-4 */

/* list_files_readdir_r.c

   Demonstrate the use of opendir() and readdir_r() to list files
   in a directory.

   Usage: list_files_readdir_r [dir...]

   Walks through each directory named on the command line (current directory
   if none are specified) to display a list of the files it contains.

   See also list_files_readdir.c.
*/
#if defined(__APPLE__)
        /* Darwin requires this header before including <dirent.h> */
#include <sys/types.h>
#endif
#include <dirent.h>
#include <errno.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void             /* List all files in directory 'dirpath' */
listFiles(const char *dirpath)
{
    DIR *dirp;
    bool           isCurrent; /* True if 'dirpath' is "." */
    struct dirent *result, *entryp;
    int nameMax;

    isCurrent = strcmp(dirpath, ".") == 0;

    /* On Linux, NAME_MAX is defined in <limits.h>. However, this limit
       may vary across file systems, so we really should use pathconf()
       to find the true limit for this file system. */

    nameMax = pathconf(dirpath, _PC_NAME_MAX);
    if (nameMax == -1)          /* Indeterminate or error */
        nameMax = 255;          /* So take a guess */

    entryp
        = (struct dirent*)malloc(offsetof(struct dirent, d_name) + nameMax + 1);
    if (entryp == NULL) {
        printf("malloc failed");
        return;
    }
    // TODO: need to free entryp before return.

    /* Open the directory - on failure print an error and return */

    dirp = opendir(dirpath);
    if (dirp == NULL) {
        printf("opendir failed on '%s'", dirpath);
        free(entryp);
        return;
    }

    /* Look at each of the entries in this directory */

    for (;;) {
        errno = readdir_r(dirp, entryp, &result);
        if (errno != 0) {
            printf("readdir_r failed\n");
            return;
        }

        if (result == NULL)     /* End of stream */
            break;

        /* Skip . and .. */

        if (strcmp(entryp->d_name, ".") == 0 ||
                strcmp(entryp->d_name, "..") == 0)
            continue;

        /* Print directory + filename */

        if (!isCurrent) printf("%s/", dirpath);
        printf("%s\n", entryp->d_name);
    }

    if (closedir(dirp) == -1) {
        printf("closedir failed\n");
        return;
    }
}

int
main(int argc, char *argv[])
{
    if (argc == 1)              /* No arguments - use current directory */
        listFiles(".");
    else
        for (argv++; *argv; argv++)
            listFiles(*argv);
    exit(EXIT_SUCCESS);
}
