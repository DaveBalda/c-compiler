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
Token generateNumber(char *curr, FILE *file){
    Token token;
    token.type = INT;
    int _calc = 0;

    while(*curr != EOF){
        if(!isdigit(*curr))
            break;
        
        _calc = (_calc * 10) + (*curr - '0');
        *curr = fgetc(file);
    }

    token.value = toCharArray(_calc);

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
Token generateKeyword(char *curr, FILE *file){
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

    token.value = calloc(_iter+1, sizeof(char));
    strcpy(token.value, buffer);
    strcat(token.value, "\0");

    if(strcmp(buffer, "fora") == 0)
        token.type = KEYWORD;

    free(buffer);

    return token;
}

/**
 * Handles the generation of a token with SEPARATOR as
 * a TokenType.
 * 
 * @param curr Current character
 * @return Token 
 */
Token generateSeparator(char* curr){
    Token token;
    token.type = SEPARATOR;

    token.value = calloc(2, sizeof(char));
    strcpy(token.value, curr);
    strcat(token.value, "\0");

    return token;
}

/**
 * Prints a token value and type.
 * 
 * @param token Token to print
 */
void printToken(Token token){
    switch (token.type)
    {
    case INT:
        printf("> TOKEN FOUND!\n  Value: %s\t  Type: INT\n", token.value);
        break;
    case KEYWORD:
        printf("> TOKEN FOUND!\n  Value: %s\t  Type: KEYWORD\n", token.value);
        break;
    case SEPARATOR:
        printf("> TOKEN FOUND!\n  Value: %s\t  Type: SEPARATOR\n", token.value);
        break;    
    default:
        break;
    }
}

/**
 * Main Lexer function that iterates on the
 * whole file and searches for tokens.
 * 
 * @param file File to iterate in
 */
void lexer(FILE *file){
    char curr = fgetc(file);
    while(curr != EOF){
        Token tok;
        if(curr == ';' || curr == '(' || curr == ')'){
            tok = generateSeparator(&curr);
            printToken(tok);
            curr = fgetc(file);
        }
        if(isdigit(curr)){
            tok = generateNumber(&curr, file);
            printToken(tok);
        }
        if(isalpha(curr)){
            tok = generateKeyword(&curr, file);
            printToken(tok);
        }
    }
}