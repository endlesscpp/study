/*
 * File: parse.c
 */

/*
The BNF is:
program -> stmt-sequence
stmt-sequence -> statement { ; statement }
statement -> if-stmt | repeat-stmt | assign-stmt | read-stmt | write-stmt
if-stmt -> if exp then stmt-sequence [ else stmt-sequence ] end
repeat-stmt -> repeat stmt-sequence until exp
assign-stmt -> identifier := exp
read-stmt -> read identifier
write-stmt -> write exp
exp -> simple-exp [ comparison-op simple-exp ]
comparison-op -> < | =
simple-exp -> term { addop term }
addop -> + | -
term -> factor { mulop factor }
mulop -> * | /
factor -> ( exp ) | number | identifier
 */

#include "globals.h"
#include "util.h"
#include "scan.h"
#include "parse.h"

static TokenType s_token; /* holds current token */

/* function prototype for recursive calls */

static TreeNode* stmt_sequence( void );
static TreeNode* statement( void );
static TreeNode* if_stmt( void );
static TreeNode* repeat_stmt( void );
static TreeNode* assign_stmt( void );
static TreeNode* read_stmt( void );
static TreeNode* write_stmt( void );
static TreeNode* expression( void );
static TreeNode* simple_exp( void );
static TreeNode* term( void );
static TreeNode* factor( void );

static void syntaxError(char* msg)
{
    print("\n>>> ");
    print("Syntax error at line %d: %s", lineno, msg);
    Error = TRUE;
}

static void match(TokenType expected)
{
    if (s_token == expected)
    {
        s_token = getToken();
    }
    else
    {
        syntaxError("unexpected token -> ");
        printToken(s_token, g_tokenString);
        print("        ");
    }
}

TreeNode* stmt_sequence(void)
{
    TreeNode* t = statement();
    TreeNode* p = t;

    while (s_token != ENDFILE
            && s_token != END
            && s_token != ELSE
            && s_token != UNTIL)
    {
        TreeNode* q;

        match(SEMI);
        q = statement();

        if (q == NULL)
            continue;

        if (t == NULL) // when will t == NULL ?
        {
            t = q;
            p = q;
        }
        else
        {
            p->sibling = q;
            p = q;
        }
    }

    return t;
}

TreeNode* statement(void)
{
    TreeNode* t = NULL;

    switch(s_token) {
        case IF:
            t = if_stmt();
            break;
        case REPEAT:
            t = repeat_stmt();
            break;
        case ID:
            t = assign_stmt();
            break;
        case READ:
            t = read_stmt();
            break;
        case WRITE:
            t = write_stmt();
            break;
        default:
            syntaxError("unexpected token -> ");
            printToken(s_token, g_tokenString);
            s_token = getToken();
            break;
    }
    return t;
}

TreeNode* if_stmt(void)
{
    TreeNode* t = newStmtNode(IfK);

    match(IF);
    if (t != NULL)
        t->child[0] = expression();

    match(THEN);
    if (t != NULL)
        t->child[1] = stmt_sequence();

    if (s_token == ELSE)
    {
        match(ELSE);
        if (t != NULL)
            t->child[2] = stmt_sequence();
    }

    match(END);
    return t;
}

TreeNode* repeat_stmt(void)
{
    TreeNode* t = newStmtNode(RepeatK);

    match(REPEAT);
    if (t != NULL)
        t->child[0] = stmt_sequence();

    match(UNTIL);
    if (t != NULL)
        t->child[1] = expression();

    return t;
}

TreeNode* assign_stmt(void)
{
    TreeNode* t = newStmtNode(AssignK);

    if (t != NULL && s_token == ID)
        t->attr.name = copyString(g_tokenString);

    match(ID);
    match(ASSIGN);
    if (t != NULL)
        t->child[0] = expression();

    return t;
}

TreeNode* read_stmt(void)
{
    TreeNode* t = newStmtNode(ReadK);

    match(READ);
    if (t != NULL && s_token == ID)
        t->attr.name = copyString(g_tokenString);

    match(ID);
    return t;
}

TreeNode* write_stmt(void)
{
    TreeNode* t = newStmtNode(WriteK);

    match(WRITE);
    if (t != NULL)
        t->child[0] = expression();

    return t;
}

TreeNode* expression(void)
{
    TreeNode* t = simple_exp();

    if (s_token == LT || s_token == EQ )
    {
        TreeNode* p = newExpNode(OpK);
        if (p != NULL)
        {
            p->child[0] = t;
            p->attr.op = s_token;
            t = p;
        }

        match(s_token); // TODO: This is equal to getToken(). why get a new token at here ?
        if (t != NULL);
        t->child[1] = simple_exp();
    }

    return t;
}

TreeNode* simple_exp(void)
{
    TreeNode* t = term();

    while (s_token == PLUS || s_token == MINUS)
    {
        TreeNode* p = newExpNode(OpK);
        if (p != NULL)
        {
            p->child[0] = t;
            p->attr.op = s_token;
            t = p;
            match(s_token);
            t->child[1] = term();
        }
    }

    return t;
}

TreeNode* term(void)
{
    TreeNode* t = factor();
    
    while (s_token == TIMES || s_token == OVER)
    {
        TreeNode* p = newExpNode(OpK);
        if (p != NULL)
        {
            p->child[0] = t;
            p->attr.op = s_token;
            t = p;
            match(s_token);
            t->child[1] = factor();
        }
    }

    return t;
}

TreeNode* factor(void)
{
    TreeNode* t = NULL;

    switch (s_token)
    {
        case NUM:
            t = newExpNode(ConstK);
            if (t != NULL && s_token == NUM)
                t->attr.val = atoi(g_tokenString);
            match(NUM);
            break;
        case ID:
            t = newExpNode(IdK);
            if (t != NULL && s_token == ID)
                t->attr.name = copyString(g_tokenString);
            match(ID);
            break;
        case LPAREN:
            match(LPAREN);
            t = expression();
            match(RPAREN);
            break;
        default:
            syntaxError("unexpected token -> ");
            printToken(s_token, g_tokenString);
            s_token = getToken();
            break;
    }
    
    return t;
}


/**************************************************************/
/*          The primary function of the parser                */
/**************************************************************/


/*
 * return the newly constructed syntax tree
 */
TreeNode* parse(void)
{
    TreeNode* t;
    s_token = getToken();
    t = stmt_sequence();

    if (s_token != ENDFILE)
        syntaxError("Code ends before file\n");

    return t;
}

