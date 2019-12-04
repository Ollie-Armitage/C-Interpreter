#ifndef COMPILER_2_0_INTERPRET_H
#define COMPILER_2_0_INTERPRET_H

#include "environment.h"
#include "Lexer_Parser_Files/nodes.h"


VALUE *block_method(NODE *block, ENV *e);
VALUE *return_method(NODE *tree, ENV *e);
VALUE *interpret(NODE *tree, ENV *e);
VALUE *node_to_value(NODE* tree);

#endif //COMPILER_2_0_INTERPRET_H
