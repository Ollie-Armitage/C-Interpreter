typedef struct VALUE
{
  int type;
  union {
    int integer;
    int boolean;
    char* string;
  } v;
} VALUE;
