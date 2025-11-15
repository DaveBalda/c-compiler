#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef enum {
  SEMI,
  OPEN_PAREN,
  CLOSE_PAREN,
} TypeSeparator;

typedef enum {
  EXIT,
} TypeKeyword;

typedef enum {
  INT,
} TypeLiteral;

/* --- STRUCTS --- */
typedef struct {
  TypeSeparator type;
} TokenSeparator;

typedef struct {
  TypeLiteral type;
  int value;
} TokenLiteral;

typedef struct {
    TypeKeyword type;
} TokenKeyword;

/* --- FUNCTIONS --- */
TokenLiteral generate_number(char *curr, FILE *file){
    TokenLiteral token;
    token.type = INT;
    token.value = 0;

    // Counts digits
    while(*curr != EOF){
        if(!isdigit(*curr))
            break;
        
        token.value = (token.value * 10) + (*curr - '0');
        *curr = fgetc(file);
    }

    return token;
}

TokenKeyword generate_keyword(char *curr, FILE *file){
    TokenKeyword token;

    char *buffer;
    int _iter = 0;

    while(*curr != EOF){
        if(!isalpha(*curr))
            break;
        _iter++;
        if(_iter == 1){
            buffer = malloc(sizeof(char));
            buffer[_iter-1] = *curr;
        } else {
            buffer = realloc(buffer, _iter * sizeof(char));
            buffer[_iter-1] = *curr;
        }
        *curr = fgetc(file);
    }

    if(strcmp(buffer, "fora") == 0)
        token.type = EXIT;

    free(buffer);

    return token;
}

void lexer(FILE *file){
    char curr = fgetc(file);
    while(curr != EOF){
        if(curr == ';'){
            printf("SEMI: found\n");
            curr = fgetc(file);
        }
        if(curr == '('){
            printf("OPEN_PAREN: found!\n");
            curr = fgetc(file);
        }
        if(curr == ')'){
            printf("CLOSE_PAREN: found!\n");
            curr = fgetc(file);
        }
        if(isdigit(curr)){
            TokenLiteral tok = generate_number(&curr, file);
            printf("TOKEN LITERAL: %d\n", tok.value);
        }
        if(isalpha(curr)){
            TokenKeyword tok = generate_keyword(&curr, file);
            if(tok.type == EXIT)
                printf("TOKEN KEYWORD: found an exit!\n");
        }
    }
}

int main() {
    FILE *file;
    file = fopen("test.mud", "r");

    if(file == NULL){
        printf("Error trying to open file...\n");
        return -1;
    }

    lexer(file);
    fclose(file);
}