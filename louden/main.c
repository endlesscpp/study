/*
 * File: main.c
 * Main program for TINY compiler
 */
#include "globals.h"
#define NO_PARSE TRUE

#if NO_PARSE
    #include "scan.h"
#else
    // do nothing at now
#endif

int lineno = 0;
FILE* source;
FILE* listing;
FILE* code;

// set tracing flag
int EchoSource = TRUE;
int TraceScan = TRUE;

int Error = FALSE;


/***********************************************/
/*              The main function              */
/***********************************************/
void Usage(int argc, char* argv[])
{
    fprintf(stderr, "usage: %s <filename>\n", argv[0]);
}

int main(int argc, char* argv[])
{
    char src_file[20];   // source code file name
    if (argc != 2)
    {
        Usage(argc, argv);
        return 1;
    }

    strlcpy(src_file, argv[1], sizeof(src_file));
    
    source = fopen(src_file, "r");
    if (source == NULL)
    {
        fprintf(stderr, "File %s not found\n", src_file);
        return 1;
    }

    listing = stdout;
    fprintf(listing, "\nTINY COMPILATION: %s\n", src_file);

    while (getToken() != ENDFILE)
        ;

    fclose(source);

    return 0;
}

