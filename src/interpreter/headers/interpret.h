#ifndef COMPILER_2_0_INTERPRET_H
#define COMPILER_2_0_INTERPRET_H

#include "environment.h"
#include "Lexer_Parser_Files/nodes.h"

VALUE *interpreter(NODE *tree, ENV *e, int numberOfArgs, char **args);

VALUE *interpret(NODE *tree, ENV *e);

VALUE *node_to_value(NODE *tree);

VALUE *interpret_if(NODE *tree, ENV *e);

VALUE *function_definition(NODE *tree, ENV *e);

VALUE *sequence_method(NODE *tree, ENV *e);

VALUE *return_method(NODE *tree, ENV *e);

VALUE *untyped_declare_method(NODE *tree, ENV *e);

VALUE *apply(TOKEN *name, NODE *args, ENV *e);

VALUE *name_method(TOKEN *token, FRAME *frame);

VALUE *assignment(TOKEN *token, FRAME *frame, VALUE *value);

int bind_initial_args(NODE *tree, ENV *e, char **args);

VALUE *build_closure(FRAME *env, NODE *ids, NODE *body);

VALUE *declaration_method(TOKEN *token, FRAME *frame);

FRAME *extend_frame(ENV *env, NODE *ids, NODE *args);

VALUE *lexical_call_method(TOKEN *name, NODE *args, ENV *env);

VALUE *read_int();

VALUE *read_string();

#endif //COMPILER_2_0_INTERPRET_H
