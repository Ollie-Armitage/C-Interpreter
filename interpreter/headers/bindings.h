#ifndef COMPILER_2_0_BINDINGS_H
#define COMPILER_2_0_BINDINGS_H

#include <Lexer_Parser_Files/token.h>
#include "environment.h"
#include "value.h"

VALUE* name_method(TOKEN *token, FRAME *frame);
VALUE* assignment(TOKEN *token, FRAME *frame, VALUE* value);
VALUE* declaration_method(TOKEN *token, FRAME *frame);

#endif //COMPILER_2_0_BINDINGS_H
