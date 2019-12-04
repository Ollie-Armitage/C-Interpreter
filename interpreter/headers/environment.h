#ifndef COMPILER_2_0_ENVIRONMENT_H
#define COMPILER_2_0_ENVIRONMENT_H

#include "Lexer_Parser_Files/token.h"
#include "Lexer_Parser_Files/nodes.h"

typedef struct binding{
    TOKEN* name;
    struct VALUE* val;
    struct BINDING* next;
} BINDING;

typedef struct frame {
    BINDING* bindings;
    struct FRAME* next;
} FRAME;

typedef struct closure {
    FRAME *env;
    NODE *ids;
    NODE *body;
} CLOSURE;

typedef struct VALUE
{
    int type;
    union {
        long int integer;
        int boolean;
        char* string;
        CLOSURE* closure;
    } v;
} VALUE;

typedef struct ENV {
    FRAME* frames;
} ENV;



#endif //COMPILER_2_0_ENVIRONMENT_H