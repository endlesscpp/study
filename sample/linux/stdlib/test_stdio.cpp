#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

int main(int argc, char** argv) {
    FILE* fp = fopen(argv[1], "r+");
    if (fp == NULL) {
        // if not exists, open with "w+"
        fp = fopen(argv[1], "w+"); 
        if (fp == NULL) {
            return -1;
        }
    }


    rewind(fp);

    int32_t count = 0;
    size_t szRead = fread(&count, sizeof(int32_t), 1, fp);
    printf("size read = %d, count = %d\n", (int)szRead, count);

    count++;
    fseek(fp, 0, SEEK_SET);
    size_t szWrite = fwrite(&count, sizeof(int32_t), 1, fp);
    printf("size write = %d\n", (int)szWrite);

    fflush(fp);

    // do no close at now
    return 0;
}




    
