#ifndef COMPILER_2_0_ARITHMETIC_TESTS_C
#define COMPILER_2_0_ARITHMETIC_TESTS_C

#include <interpreter/headers/arithmetic.h>
#include <Lexer_Parser_Files/C.tab.h>
#include <assert.h>
#include <stdio.h>


int add_method_test(){

    TOKEN* V_1 = new_token(CONSTANT);
    TOKEN* V_2 = new_token(CONSTANT);
    ENV* e = NULL;

    int i;

    for(i = -10; i < 11; i++){
        V_1->value = i;
        V_2->value = i+5;

        NODE* node = make_node('+', make_leaf(V_1), make_leaf(V_2));

        VALUE* answer = add_method(node->left, node->right, e);

        assert(answer->v.integer == (i+(i+5)));

    }
    printf("add_method() works for values between -10 and 10.\n");


    return 0;
}

#endif //COMPILER_2_0_ARITHMETIC_TESTS_C