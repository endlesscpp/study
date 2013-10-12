/*
 * File: scan.h
 */

#ifndef _SCAN_H_
#define _SCAN_H_

#define MAX_TOKEN_LEN 40

/* array store the lexme of each token */
extern char tokenString[MAX_TOKEN_LEN+1];

/* function returns the next token in source file */
TokenType getToken(void);



#endif // _SCAN_H_
