#include <stdio.h>
#include <stdlib.h>

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

int main() {
  printf("Hello, world!\n");
  return 0;
}