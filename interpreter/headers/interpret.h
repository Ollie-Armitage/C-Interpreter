#ifndef COMPILER_2_0_INTERPRET_H
#define COMPILER_2_0_INTERPRET_H

#include "environment.h"
#include "Lexer_Parser_Files/nodes.h"

VALUE *interpret(NODE *tree, ENV *e);
VALUE *node_to_value(NODE* tree);

#endif //COMPILER_2_0_INTERPRET_H
