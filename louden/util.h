/*
 * File: util.h
 */

#ifndef _UTIL_H_
#define _UTIL_H_

/* procedure printToken() prints a token
 * and its lexme to the listing file
 */
void printToken(TokenType, const char* tokenString);

/*
 * print to the listing file
 */
void print(const char* format, ...);

/*
 * create a new statement node for syntax tree construction
 */
TreeNode* newStmtNode(StmtKind);

/*
 * create a new expression node for syntax tree construction
 */
TreeNode* newExpNode(ExpKind);

/*
 * allocates and makes a new copy of the input string
 */
char* copyString(char*);

/*
 * print a syntax tree to the listing file using indentation to indicate subtree
 */
void printTree(TreeNode*);


#endif //_UTIL_H_
