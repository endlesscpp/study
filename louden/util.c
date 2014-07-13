/*
 * File: util.c
 */
#include "globals.h"
#include "util.h"

void print(const char* format, ...)
{
    va_list ap;
    va_start(ap, format);
    vfprintf(listing, format, ap);
    va_end(ap);
}

/* prints a token and its lexme to the listing file */
void printToken(TokenType token, const char* tokenString)
{
    switch (token)
    {
        case IF:
        case THEN:
        case ELSE:
        case END:
        case REPEAT:
        case UNTIL:
        case READ:
        case WRITE:
            print("reserved word: %s\n", tokenString);
            break;
        case ASSIGN:
            print(":=\n"); 
            break;
        case LT:
            print("<\n");
            break;
        case EQ:
            print("=\n");
            break;
        case LPAREN:
            print("(\n");
            break;
        case RPAREN:
            print(")\n");
            break;
        case SEMI:
            print(";\n");
            break;
        case PLUS:
            print("+\n");
            break;
        case MINUS:
            print("-\n");
            break;
        case TIMES:
            print("*\n");
            break;
        case OVER:
            print("/\n");
            break;
        case ENDFILE:
            print("EOF\n");
            break;
        case NUM:
            print("NUM, val = %s\n", tokenString);
            break;
        case ID:
            print("ID, name = %s\n", tokenString);
            break;
        case ERROR:
            print("ERROR, %s\n", tokenString);
            break;
        default: /* should never happen */
            print("Unknown token: %d\n", token);
    }
}

TreeNode* newStmtNode(StmtKind kind)
{
    TreeNode* t = (TreeNode*)malloc(sizeof(TreeNode));
    int i;

    if (t==NULL)
    {
        print("Out of memory error at line %d\n", lineno);
        return NULL;
    }

    for (i = 0; i < MAX_CHILDREN; i++)
        t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = StmtK;
    t->kind.stmt = kind;
    t->lineno = lineno;

    return t;
}

TreeNode* newExpNode(ExpKind kind)
{
    TreeNode* t = (TreeNode*)malloc(sizeof(TreeNode));
    int i;

    if (t == NULL)
    {
        print("Out of memory error at line %d\n", lineno);
        return NULL;
    }

    for (i = 0; i < MAX_CHILDREN; i++)
        t->child[i] = NULL;

    t->sibling = NULL;
    t->nodekind = ExpK;
    t->kind.exp = kind;
    t->lineno = lineno;
    t->type = Void;

    return t;
}

char* copyString(char* s)
{
    return strdup(s);
}

/* used by printTree() to store the current number of spaces to indent */
static int s_indentno = 0;

#define INDENT      s_indentno += 4
#define UNINDENT    s_indentno -= 4

static void printSpaces(void)
{
    int i;
    for (i = 0; i < s_indentno; i++)
        print(" ");
}

static void printStmtNode(TreeNode* tree)
{
    switch (tree->kind.stmt)
    {
        case IfK:
            print("If\n");
            break;
        case RepeatK:
            print("Repeat\n");
            break;
        case AssignK:
            print("Assign to: %s\n", tree->attr.name);
            break;
        case ReadK:
            print("Read: %s\n", tree->attr.name);
            break;
        case WriteK:
            print("Write\n");
            break;
        default:
            print("Unknown ExpNode kind\n");
            break;
    }
}

static void printExpNode(TreeNode* tree)
{
    switch (tree->kind.exp)
    {
        case OpK:
            print("Op: ");
            printToken(tree->attr.op, "\0"); // TODO: why use \0?
            break;
        case ConstK:
            print("const: %d\n", tree->attr.val);
            break;
        case IdK:
            print("Id: %s\n", tree->attr.name);
            break;
        default:
            print("Unknown ExpNode kind\n");
            break;
    }
}

void printTree(TreeNode* tree)
{
    int i;
    INDENT;

    while (tree != NULL)
    {
        printSpaces();
        if (tree->nodekind == StmtK)
        {
            printStmtNode(tree);
        }
        else if(tree->nodekind == ExpK)
        {
            printExpNode(tree);
        }
        else
        {
            print("Unknown node kind\n");
        }

        for (i = 0; i < MAX_CHILDREN; i++)
            printTree(tree->child[i]);

        tree = tree->sibling;
    }

    UNINDENT;
}

