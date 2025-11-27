#include <ctype.h>
#include <string.h>
#include <math.h>

#include "lexer.h"

/**
 * Transforms an integer to a char array.
 * It's a helper function needed to match the
 * token value type.
 * 
 * @param number Integer to transform
 * @return char* 
 */
char* toCharArray(int number) {
    int size = floor(log10(number) + 1);
    if(number == 0){
        char *numberArray = calloc(2, sizeof(char));
        numberArray[0] = '0';
        numberArray[1] = '\0';
        return numberArray;
    }
    char *numberArray = calloc(size+1, sizeof(char));

    int i;
    for(i = size-1; i >= 0; --i, number/=10){
        numberArray[i] = (number % 10) + '0';
    }

    numberArray[size] = '\0';

    return numberArray;
}

/**
 * Handles the generation of a token with INT as
 * a TokenType. It calculates the final value of
 * a number until it reaches the end of the digits
 * and then memorizes the value inside the token value
 * with a helper function toCharArray.
 * 
 * @param curr Current character
 * @param file Current readable file
 * @return Token 
 */
Token *generateNumber(char *curr, FILE *file){
    Token *token = malloc(sizeof(Token));
    token->type = INT;
    int _calc = 0;

    while(*curr != EOF){
        if(!isdigit(*curr))
            break;
        
        _calc = (_calc * 10) + (*curr - '0');
        *curr = fgetc(file);
    }

    token->value = toCharArray(_calc);

    return token;
}

/**
 * Handles the generation of a token with KEYWORD as
 * a TokenType. It first creates a dynamically growing
 * buffer to contain the final keyword, then it executes
 * a strcpy to the token value.
 * 
 * @param curr Current character
 * @param file Current readable file
 * @return Token 
 */
Token *generateKeyword(char *curr, FILE *file){
    Token *token = malloc(sizeof(Token));

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

    token->value = calloc(_iter+1, sizeof(char));
    strcpy(token->value, buffer);
    free(buffer);

    token->value[_iter] = '\0';

    if(strcmp(token->value, "fora") == 0)
        token->type = KEYWORD;

    return token;
}

/**
 * Handles the generation of a token with SEPARATOR as
 * a TokenType.
 * 
 * @param curr Current character
 * @return Token 
 */
Token *generateSeparator(char* curr){
    Token *token = malloc(sizeof(Token));
    token->type = SEPARATOR;

    token->value = calloc(2, sizeof(char));
    token->value[0] = *curr;
    token->value[1] = '\0';

    return token;
}

/**
 * Returns true if the character is a 
 * separator.
 * 
 * @param curr Character to check
 * @return True (1) or False (0)
 */
int isSeparator(char curr){
    if(curr == ';' || curr == '(' || curr == ')')
        return 1;
    return 0;
}

/**
 * Prints a token list.
 * 
 * @param list Token list to print
 * @param length List length
 */
void printTokenList(Token *list, size_t length) {
    for(size_t i=0; i<length; i++) {
        switch(list[i].type)
        {
        case INT:
            printf("[TOKEN] Value: %s\t  Type: INT\n", list[i].value);
            break;
        case KEYWORD:
            printf("[TOKEN] Value: %s\t  Type: KEYWORD\n", list[i].value);
            break;
        case SEPARATOR:
            printf("[TOKEN] Value: %s\t  Type: SEPARATOR\n", list[i].value);
            break;    
        default:
            break;
        }
    }
}

/**
 * Main Lexer.
 * 
 * @param file File to search tokens
 * @param length Length of the list
 * @return Token* Token list
 */
Token *lexer(FILE *file, size_t *length){
    char curr = fgetc(file);

    Token *tokenList;

    while(curr != EOF){
        Token *_tok;
        
        if(isSeparator(curr)){
            _tok = generateSeparator(&curr);
            curr = fgetc(file);
            (*length)++;
        }
        else if(isdigit(curr)){
            _tok = generateNumber(&curr, file);
            (*length)++;
        }
        else if(isalpha(curr)){
            _tok = generateKeyword(&curr, file);
            (*length)++;
        }
        else 
            continue;

        if((*length) == 1){
            tokenList = malloc(sizeof(Token));

            tokenList[(*length)-1].type = _tok->type;
            int _tsize = strlen(_tok->value);
            tokenList[(*length)-1].value = malloc(_tsize * sizeof(char));
            strcpy(tokenList[(*length)-1].value, _tok->value);
        }
        else{
            tokenList = realloc(tokenList, (*length) * sizeof(Token));

            tokenList[(*length)-1].type = _tok->type;
            int _tsize = strlen(_tok->value);
            tokenList[(*length)-1].value = malloc(_tsize * sizeof(char));
            strcpy(tokenList[(*length)-1].value, _tok->value);
        }

        free(_tok);
    }

    return tokenList;
}