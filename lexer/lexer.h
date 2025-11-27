#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>

typedef enum {
    INT,
    KEYWORD,
    SEPARATOR,
} TokenType;

typedef struct {
    TokenType type;
    char *value;
} Token;

Token *generateNumber(char *curr, FILE *file);
Token *generateKeyword(char *curr, FILE *file);
Token *generateSeparator(char *curr);
Token *lexer(FILE *file, size_t *length);

int isSeparator(char curr);
void printTokenList(Token *token, size_t length);

#endif