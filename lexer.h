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

Token generate_number(char *curr, FILE *file);
Token generate_keyword(char *curr, FILE *file);
void lexer(FILE *file);

#endif