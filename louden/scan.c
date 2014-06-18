/*
 * File: scan.c
 * The scanner implementation for the TINY compiler
 */
#include "globals.h"
#include "util.h"
#include "scan.h"

/* state in scanner DFA */
typedef enum
{
    START,
    INASSIGN,
    INCOMMENT,
    INNUM,
    INID,
    DONE
} StateType;

/* lexme of identifier or reserved word */
char g_tokenString[MAX_TOKEN_LEN + 1];

/* length of the input buffer for source code lines */
#define BUF_CAPACITY 256

static char lineBuf[BUF_CAPACITY];   /* hold the current line */
static int  linepos = 0;        /* current position in LineBuf */
static int  bufsize = 0;        /* current size of buffer string */

/*
 * Feteches the next non-blank character from lineBuf,
 * reading in a new line if lineBuf is exhausted
 */
static char getNextChar(void)
{
    if (linepos >= bufsize)
    {
        lineno++;

        if (fgets(lineBuf, BUF_CAPACITY - 1, source) == 0)
            return EOF;

        if (EchoSource)
            print("%4d: %s", lineno, lineBuf);

        bufsize = strlen(lineBuf);
        linepos = 0;
    }

    return lineBuf[linepos++];
}

/* backtrack one character in lineBuf */
static void ungetNextChar(void)
{
    linepos--;
}

/* lookup table of reserved words */
struct ReservedWord
{
    char* str;
    TokenType tok;
};

struct ReservedWord reservedWords[] = 
{
    {"if",      IF},
    {"then",    THEN},
    {"else",    ELSE},
    {"end",     END},
    {"repeat",  REPEAT},
    {"until",   UNTIL},
    {"read",    READ},
    {"write",   WRITE},
};


static TokenType reservedLookup(char* s)
{
    int i;
    for (i = 0; i<sizeof(reservedWords)/sizeof(reservedWords[0]); i++)
    {
        if (strcmp(s, reservedWords[i].str) ==0)
            return reservedWords[i].tok;
    }
    return ID;
}

/* The primary function of scanner */
TokenType getToken(void)
{
    TokenType   currToken;              // current token to be returned
    StateType   state = START;          // current state
    int         tokenStringIndex = 0;   // the index for storing into tokenString
    int         save;                   // flag to indicate save to tokenString

    while (state != DONE)
    {
        char c = getNextChar();
        save = TRUE;

        switch (state)
        {
            case START:
                if (isdigit(c))
                    state = INNUM;
                else if (isalpha(c))
                    state = INID;
                else if (c == ':')
                    state = INASSIGN;
                else if (c == ' ' || c == '\t' || c == '\n')
                    save = FALSE;
                else if (c == '{')
                {
                    save = FALSE;
                    state = INCOMMENT;
                }
                else
                {
                    state = DONE;
                    switch (c)
                    {
                        case EOF:
                            save = FALSE;
                            currToken = ENDFILE;
                            break;
                        case '=':
                            currToken = EQ;
                            break;
                        case '<':
                            currToken = LT;
                            break;
                        case '+':
                            currToken = PLUS;
                            break;
                        case '-':
                            currToken = MINUS;
                            break;
                        case '*':
                            currToken = TIMES;
                            break;
                        case '/':
                            currToken = OVER;
                            break;
                        case '(':
                            currToken = LPAREN;
                            break;
                        case ')':
                            currToken = RPAREN;
                            break;
                        case ';':
                            currToken = SEMI;
                            break;
                        default:
                            currToken = ERROR;
                            break;
                    }
                }
                break;
            case INCOMMENT:
                save = FALSE;
                if (c == '}')
                    state = START;
                break;
            case INASSIGN:
                state = DONE;
                if (c == '=')
                {
                    currToken = ASSIGN;
                }
                else
                {
                    /* backup in the input */
                    ungetNextChar();
                    save = FALSE;
                    currToken = ERROR;
                }
                break;
            case INNUM:
                if (!isdigit(c))
                {
                    ungetNextChar();
                    save = FALSE;
                    state = DONE;
                    currToken = NUM;
                }
                break;
            case INID:
                if (!isalpha(c))
                {
                    ungetNextChar();
                    save = FALSE;
                    state = DONE;
                    currToken = ID;
                }
                break;
            case DONE:
            default:
                print("Scanner Bug: state = %d\n", state);
                state = DONE;
                currToken = ERROR;
                break;
        } //end switch( state )

        if (save && tokenStringIndex <= MAX_TOKEN_LEN)
            g_tokenString[tokenStringIndex++] = c;

        if (state == DONE)
        {
            g_tokenString[tokenStringIndex] = '\0';
            if (currToken == ID)
                currToken = reservedLookup(g_tokenString);
        }
    }// end while (state != DONE)

    if (TraceScan) 
    {
        print("\t%d: ", lineno);
        printToken(currToken, g_tokenString);
    }

    return currToken;
}

