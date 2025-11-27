#include "./lexer/lexer.h"

int main(int argc, char *argv[]) {
    if(argc < 2){
        fprintf(stderr, "Syntax error: You must specify a filename with the syntax: %s <filename.mud>\n", argv[0]);
        exit(0);
    }

    FILE *file;
    file = fopen(argv[1], "r");

    if(!file){
        printf("File error: Specified file does not exist\n");
        exit(0);
    }

    size_t listLength = 0;
    Token *list = lexer(file, &listLength);
    printTokenList(list, listLength);

    fclose(file);
    exit(1);
}