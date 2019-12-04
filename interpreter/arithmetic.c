#ifndef COMPILER_2_0_ARITHMETIC_C
#define COMPILER_2_0_ARITHMETIC_C


#include <Lexer_Parser_Files/nodes.h>
#include "headers/environment.h"
#include "headers/interpret.h"

VALUE* add_method(NODE* left, NODE* right, ENV* e){
    VALUE* answer = interpret(left, e);
    answer->v.integer = answer->v.integer + interpret(right, e)->v.integer;
    answer->type = 0;
    return answer;
}

VALUE* subtract_method(NODE* left, NODE* right, ENV* e){
    VALUE* answer = interpret(left, e);
    answer->v.integer = answer->v.integer - interpret(right, e)->v.integer;
    answer->type = 0;
    return answer;
}

VALUE* multiply_method(NODE* left, NODE* right, ENV* e){
    VALUE* answer = interpret(left, e);
    answer->v.integer = answer->v.integer * interpret(right, e)->v.integer;
    answer->type = 0;
    return answer;
}

VALUE* divide_method(NODE* left, NODE* right, ENV* e){
    VALUE* answer = interpret(left, e);
    answer->v.integer = answer->v.integer / interpret(right, e)->v.integer;
    answer->type = 0;
    return answer;
}

VALUE* LT_method(NODE* left, NODE* right, ENV* e){
    VALUE* answer = interpret(left, e);
    answer->v.boolean = answer->v.integer < interpret(right, e)->v.integer;
    answer->type = 1;
    return answer;
}

VALUE* GT_method(NODE* left, NODE* right, ENV* e){
    VALUE* answer = interpret(left, e);
    answer->v.boolean = answer->v.integer > interpret(right, e)->v.integer;
    answer->type = 1;
    return answer;}

VALUE* NE_OP_method(NODE* left, NODE* right, ENV* e){
    VALUE* answer = interpret(left, e);
    answer->v.boolean = answer->v.integer != interpret(right, e)->v.integer;
    answer->type = 1;
    return answer;
}

VALUE* EQ_OP_method(NODE* left, NODE* right, ENV* e){VALUE* answer = interpret(left, e);
    answer->v.boolean = answer->v.integer == interpret(right, e)->v.integer;
    answer->type = 1;
    return answer;}

VALUE* LE_OP_method(NODE* left, NODE* right, ENV* e){
    VALUE* answer = interpret(left, e);
    answer->v.boolean = answer->v.integer <= interpret(right, e)->v.integer;
    answer->type = 1;
    return answer;
}

VALUE* GE_OP_method(NODE* left, NODE* right, ENV* e){VALUE* answer = interpret(left, e);
    answer->v.boolean = answer->v.integer >= interpret(right, e)->v.integer;
    answer->type = 1;
    return answer;}

#endif //COMPILER_2_0_ARITHMETIC_C