typedef struct block {
    int nvars;
} BLOCK;

typedef struct call {
    TOKEN *name;
    int arity;
} CALL;

typedef struct tac {
    int op;
    union {
        BLOCK block;
        CALL call;
    } args;
    struct TAC *next;
} TAC;

typedef struct bb {
    TAC *leader;
} BB;