/*
 * Globals.h
 * global types and vars for TINY compiler
 */


/*
 * add a dummy comment to test the GIT commit
 */

/*
 * The dummy change 2 to test GIT commit
 */

/*
 * The dummy change 3
 */

#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif


typedef enum
{
    /* book-keeping tokens */
    ENDFILE,
    ERROR,
    /* reserved words */
    IF,
    THEN,
    ELSE,
    END,
    REPEAT,
    UNTIL,
    READ,
    WRITE,
    /* multiple character tokens */
    ID,
    NUM,
    /* special symbols */
    ASSIGN,
    EQ,
    LT,
    PLUS,
    MINUS,
    TIMES,
    OVER,
    LPAREN,
    RPAREN,
    SEMI,
} TokenType;


/* source code text file */
extern FILE* source;
/* listing output text file */
extern FILE* listing;
/* code text file for TM simulator */
extern FILE* code;

/* source line number for listing */
extern int lineno;

/*************************************************/
/*              Syntax tree for parsing          */
/*************************************************/

typedef enum
{
    StmtK,
    ExpK,
} NodeKind;

typedef enum
{
    IfK,
    RepeatK,
    AssignK,
    ReadK,
    WriteK,
} StmtKind;

typedef enum
{
    OpK,
    ConstK,
    IdK
} ExpKind;

/* ExpType is used for type checking */
typedef enum
{
    Void,
    Integer,
    Boolean,
} ExpType;

#define MAX_CHILDREN 3

typedef struct tagTreeNode
{
    struct tagTreeNode* child[ MAX_CHILDREN ];
    struct tagTreeNode* sibling;
    int lineno;
    NodeKind nodekind;
    union
    {
        StmtKind stmt;
        ExpKind exp;
    } kind;
    union
    {
        TokenType op;
        int val;
        char* name;
    } attr;
    ExpType type; /* for type checking of exps */
} TreeNode;


/*************************************************/
/*              Flag for tracing                 */
/*************************************************/
extern int EchoSource;

extern int TraceScan;

extern int TraceParse;

extern int TraceAnalyze;

extern int TraceCode;

extern int Error;



#endif // _GLOBALS_H_
