#ifndef COMPILER_2_0_VALUE_H
#define COMPILER_2_0_VALUE_H

typedef struct VALUE
{
  int type;
  union {
    long int integer;
    int boolean;
    char* string;
  } v;
} VALUE;

#endif //COMPILER_2_0_VALUE_H