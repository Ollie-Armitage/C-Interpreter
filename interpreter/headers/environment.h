#ifndef COMPILER_2_0_ENVIRONMENT_H
#define COMPILER_2_0_ENVIRONMENT_H

#include "Lexer_Parser_Files/token.h"
#include "Lexer_Parser_Files/nodes.h"
#include "value.h"


typedef struct binding{
    TOKEN* name;
    VALUE* val;
    struct BINDING* next;
} BINDING;

typedef struct frame {
    BINDING* bindings; 
    struct FRAME* next;
} FRAME;

typedef struct ENV {
    FRAME* frames;
} ENV;

typedef struct closure {
    FRAME *env;
    NODE *ids;
    NODE *body;
} CLOSURE;

#endif //COMPILER_2_0_ENVIRONMENT_H