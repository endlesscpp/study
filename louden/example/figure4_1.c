
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

char token; /* global token variable */

/* function prototypes for recursive calls */
float expr(void);
float term(void);
float factor(void);

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

int main(void)
{
    float result;

    /* load token with first character for lookahead */
    token = getchar();

    result = expr();
    
    if (token == '\n') /* the end of line */
        printf("Result = %f\n", result);
    else
        error(); /* extraneous chars on line*/

    return 0;
}

float expr(void)
{
    float temp = term();

    while (token == '+' || token == '-')
    {
        switch (token)
        {
            case '+':
                match('+');
                temp += term();
                break;
            case '-':
                match('-');
                temp -= term();
                break;
        }
    }
    
    return temp;
}

float term(void)
{
    float temp = factor();
    while (token == '*')
    {
        match('*');
        temp *= factor();
    }

    return temp;
}

float factor(void)
{
    float temp = 0;
    if (token == '(')
    {
        match('(');
        temp = expr();
        match(')');
    }
    else if (isdigit(token))
    {
        ungetc(token, stdin);
        scanf("%f", &temp);
        token = getchar(); /* get next char */
    }
    else
    {
        error();
    }

    return temp;
}


