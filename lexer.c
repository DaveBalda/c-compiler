#include <ctype.h>
#include <string.h>
#include <math.h>

#include "lexer.h"

char* toCharArray(int number) {
    int size = floor(log10(number) + 1);
    if(number == 0){
        char *numberArray = calloc(1, sizeof(char));
        numberArray[0] = '0';
        return numberArray;
    }
    char *numberArray = calloc(size, sizeof(char));

    int i;
    for(i = size-1; i >= 0; --i, number/=10){
        numberArray[i] = (number % 10) + '0';
    }

    return numberArray;
}

Token generate_number(char *curr, FILE *file){
    Token token;
    token.type = INT;
    int _calc = 0;

    // Counts digits
    while(*curr != EOF){
        if(!isdigit(*curr))
            break;
        
        _calc = (_calc * 10) + (*curr - '0');
        *curr = fgetc(file);
    }

    token.value = toCharArray(_calc);

    return token;
}

Token generate_keyword(char *curr, FILE *file){
    Token token;

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
        token.type = KEYWORD;

    free(buffer);

    return token;
}

void lexer(FILE *file){
    char curr = fgetc(file);
    while(curr != EOF){
        if(curr == ';'){
            printf("FOUND: ;\n");
            curr = fgetc(file);
        }
        if(curr == '('){
            printf("FOUND: (\n");
            curr = fgetc(file);
        }
        if(curr == ')'){
            printf("FOUND: )\n");
            curr = fgetc(file);
        }
        if(isdigit(curr)){
            Token tok = generate_number(&curr, file);
            printf("TOKEN LITERAL: %s\n", tok.value);
        }
        if(isalpha(curr)){
            Token tok = generate_keyword(&curr, file);
            if(tok.type == KEYWORD)
                printf("TOKEN KEYWORD: EXIT\n");
        }
    }
}