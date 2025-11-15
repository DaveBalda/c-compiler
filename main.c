#include "lexer.h"

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