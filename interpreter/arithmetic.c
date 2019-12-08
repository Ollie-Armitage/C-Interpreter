#ifndef COMPILER_2_0_ARITHMETIC_C
#define COMPILER_2_0_ARITHMETIC_C


#include <Lexer_Parser_Files/nodes.h>
#include "headers/environment.h"
#include "headers/interpret.h"
#include <interpreter/headers/environment.h>
#include "interpreter/headers/value.h"

#include <stdlib.h>

VALUE* add_method(NODE* left, NODE* right, ENV* e){
    if(left == NULL && right == NULL) return NULL;
    return make_lint_value(interpret(left, e)->v.integer + interpret(right, e)->v.integer);
}

VALUE* subtract_method(NODE* left, NODE* right, ENV* e){
    if(left == NULL && right == NULL) return NULL;
    return make_lint_value(interpret(left, e)->v.integer - interpret(right, e)->v.integer);
}

VALUE* multiply_method(NODE* left, NODE* right, ENV* e){
    if(left == NULL && right == NULL) return NULL;
   return make_lint_value(interpret(left, e)->v.integer * interpret(right, e)->v.integer);
}

VALUE* divide_method(NODE* left, NODE* right, ENV* e){
    if(left == NULL && right == NULL) return NULL;
    return make_lint_value(interpret(left, e)->v.integer / interpret(right, e)->v.integer);
}

// TODO: What about BOOL comparison with BOOL?

VALUE* LT_method(NODE* left, NODE* right, ENV* e){
    if(left == NULL && right == NULL) return NULL;
    return make_bool_value(interpret(left, e)->v.integer < interpret(right, e)->v.integer);
}

VALUE* GT_method(NODE* left, NODE* right, ENV* e){
    if(left == NULL && right == NULL) return NULL;
    return make_bool_value(interpret(left, e)->v.integer > interpret(right, e)->v.integer);
}

VALUE* NE_OP_method(NODE* left, NODE* right, ENV* e){
    if(left == NULL && right == NULL) return NULL;
    return make_bool_value(interpret(left, e)->v.integer != interpret(right, e)->v.integer);
}

VALUE* EQ_OP_method(NODE* left, NODE* right, ENV* e){
    if(left == NULL && right == NULL) return NULL;
    return make_bool_value(interpret(left, e)->v.integer == interpret(right, e)->v.integer);
}

VALUE* LE_OP_method(NODE* left, NODE* right, ENV* e){
    if(left == NULL && right == NULL) return NULL;
    return make_bool_value(interpret(left, e)->v.integer <= interpret(right, e)->v.integer);
}

VALUE* GE_OP_method(NODE* left, NODE* right, ENV* e){
    if(left == NULL && right == NULL) return NULL;
    return make_bool_value(interpret(left, e)->v.integer >= interpret(right, e)->v.integer);
}

#endif //COMPILER_2_0_ARITHMETIC_C