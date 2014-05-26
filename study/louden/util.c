/*
 * File: util.c
 */
#include "globals.h"
#include "util.h"

static void print(const char* format, ...)
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

