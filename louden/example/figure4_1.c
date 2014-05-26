
/*
 * revision 2
 * Exercise 4.31
 * Can calculate both the integer and floating-point numbers
 */

/*
 * revision 1
 * Exercise 4.30
 * rewrite the calculator to so that it computes with floating-point instead of integers
 */

/*
 * Simple integer arithmetic calculator
 * This is the sample of figure 4.1
 */

/* 
 * The calculator according to below EBNF:
 * <expr> ->  <term> { <addop> <term> }
 * <addop> -> + | -
 * <term> -> <factor> { <mulop> <factor> }
 * <mulop> -> *
 * <factor> -> ( <expr> ) | Number
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char token; /* global token variable */

enum _e_type
{
    INTEGER,
    FLOAT,
};

struct _t_value
{
    enum _e_type type;

    union
    {
        int     iVal;
        float   fVal;
    } val;
};
        

/* function prototypes for recursive calls */
struct _t_value expr(void);
struct _t_value term(void);
struct _t_value factor(void);

void error(void)
{
    fprintf(stderr, "Error\n");
    exit(1);
}

void match(char expectedToken)
{
    if (token == expectedToken)
        token = getchar();
    else
        error();
}

static void printTValue( struct _t_value v )
{
    if (v.type == INTEGER)
        printf("Result = %d\n", v.val.iVal);
    else /* floating-point number */
        printf("Result = %f\n", v.val.fVal);
}

float getVal(struct _t_value v)
{
    if (v.type == INTEGER)
        return v.val.iVal;
    else
        return v.val.fVal;
}

static enum _e_type getType(struct _t_value v)
{
    return v.type;
}

static struct _t_value addVal(struct _t_value v1, struct _t_value v2)
{
    struct _t_value ret;

    if (getType(v1) == INTEGER && getType(v2) == INTEGER)
    {
        ret.type = INTEGER;
        ret.val.iVal = v1.val.iVal + v2.val.iVal;
    }
    else
    {
        ret.type = FLOAT;
        ret.val.fVal = getVal(v1) + getVal(v2);
    }

    return ret;
}

static struct _t_value subVal(struct _t_value v1, struct _t_value v2)
{
    struct _t_value ret;

    if (getType(v1) == INTEGER && getType(v2) == INTEGER)
    {
        ret.type = INTEGER;
        ret.val.iVal = v1.val.iVal - v2.val.iVal;
    }
    else
    {
        ret.type = FLOAT;
        ret.val.fVal = getVal(v1) - getVal(v2);
    }

    return ret;
}

static struct _t_value mulVal(struct _t_value v1, struct _t_value v2)
{
    struct _t_value ret;

    if (getType(v1) == INTEGER && getType(v2) == INTEGER)
    {
        ret.type = INTEGER;
        ret.val.iVal = v1.val.iVal * v2.val.iVal;
    }
    else
    {
        ret.type = FLOAT;
        ret.val.fVal = getVal(v1) * getVal(v2);
    }

    return ret;
}


int main(void)
{
    struct _t_value result;

    /* load token with first character for lookahead */
    token = getchar();

    result = expr();
    
    if (token == '\n') /* the end of line */
        printTValue(result);
    else
        error(); /* extraneous chars on line*/

    return 0;
}

struct _t_value expr(void)
{
    struct _t_value temp = term();

    while (token == '+' || token == '-')
    {
        switch (token)
        {
            case '+':
                match('+');
                temp = addVal(temp, term());
                break;
            case '-':
                match('-');
                temp = subVal(temp, term());
                break;
        }
    }
    
    return temp;
}

struct _t_value term(void)
{
    struct _t_value temp = factor();
    while (token == '*')
    {
        match('*');
        temp = mulVal(temp, factor());
    }

    return temp;
}

struct _t_value factor(void)
{
    struct _t_value v = {0};
    if (token == '(')
    {
        match('(');
        v = expr();
        match(')');
    }
    else if (isdigit(token))
    {
        int iVal = 0;
        ungetc(token, stdin);
        scanf("%d", &iVal);

        token = getchar(); /* get next char */

        if (token == '.') /* a floating point number */
        {
            v.type = FLOAT;
            v.val.iVal = iVal;
            
            scanf("%d", &iVal);
            int divisor = 1;
            int temp = iVal;
            while (temp)
            {
                divisor *= 10;
                temp /= 10;
            }

            v.val.fVal = v.val.iVal + ((float)iVal) / divisor;
            token = getchar();
        }
        else
        {
            v.type = INTEGER;
            v.val.iVal = iVal;
        }

    }
    else
    {
        error();
    }

    return v;
}


