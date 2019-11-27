#ifndef COMPILER_2_0_INTERPRET_C
#define COMPILER_2_0_INTERPRET_C

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <Lexer_Parser_Files/C.tab.h>
#include <interpreter/headers/bindings.h>
#include <interpreter/headers/arithmetic.h>
#include <interpreter/headers/interpret.h>


VALUE *interpret(NODE *tree, ENV *e) {
   if (tree == NULL) return NULL;
    if (tree->type == LEAF) { return interpret(tree->left, e); }
    else if (tree->type == INT || tree->type == FUNCTION || tree->type == VOID) {}
    else if (tree->type == IDENTIFIER) { return name_method((TOKEN *) tree, e->frames); }
    else if (tree->type == CONSTANT || tree->type == STRING_LITERAL) { return node_to_value(tree); }
    else if (tree->type == RETURN) {
        VALUE* answer = return_method(tree->left, e);
        //free(answer);
    }
    else if (tree->type == '~') {
        if (tree->right->type == LEAF) declaration_method((TOKEN *) tree->right->left, e->frames);
        else declaration_method((TOKEN *) tree->right->left->left, e->frames);
    } else if (tree->type == APPLY) {}
    else if (tree->type == '=') { assignment((TOKEN *) tree->left->left, e->frames, interpret(tree->right, e)); }
    else if (tree->type == '+') { return add_method(tree->left, tree->right, e); }
    else if (tree->type == '-') { return subtract_method(tree->left, tree->right, e); }
    else if (tree->type == '*') { return multiply_method(tree->left, tree->right, e); }
    else if (tree->type == '/') { return divide_method(tree->left, tree->right, e); }
    else if (tree->type == GE_OP) { return GE_OP_method(tree->left, tree->right, e); }
    else if (tree->type == LE_OP) { return LE_OP_method(tree->left, tree->right, e); }
    else if (tree->type == NE_OP) { return NE_OP_method(tree->left, tree->right, e); }
    else if (tree->type == EQ_OP) { return EQ_OP_method(tree->left, tree->right, e); }
    else if (tree->type == '<') { return LT_method(tree->left, tree->right, e); }
    else if (tree->type == '>') { return GT_method(tree->left, tree->right, e); }
    else {
        return block_method(tree->left, e);
    }
}

VALUE *node_to_value(NODE *node) {
    TOKEN *n = (TOKEN *) node;
    VALUE *endValue = malloc(sizeof(VALUE));

    if (n->type == CONSTANT) {
        endValue->type = 0;
        endValue->v.integer = n->value;//
        return endValue;
    } else if (n->type == STRING_LITERAL) {
        endValue->type = 2;
        endValue->v.string = n->lexeme;
        return endValue;
    }

    free(endValue);
    return NULL;
}


VALUE *block_method(NODE *block, ENV *e) {
    while (block != NULL) {
        interpret(block, e);
        block = block->right;
    }
}

VALUE *return_method(NODE *tree, ENV *e) {
    VALUE *answer = interpret(tree, e);

    if (answer == NULL) {
        return NULL;
    }

    if (answer->type == 0) {
        printf("\nAnswer: %d\n\n", answer->v.integer);
        return answer;
    } else if (answer->type == 1) {
        if (answer->v.boolean == 0) {
            printf("\nAnswer: False\n\n");
            return (VALUE *) 0;
        } else if (answer->v.boolean == 1) {
            printf("\nAnswer: True\n\n");
            return (VALUE *) 1;
        }
    } else if (answer->type == 2) {
        printf("\nAnswer: %s\n\n", answer->v.string);
        return answer;
    } else {
        printf("\nAnswer: No valid return type.\n\n");
        free(answer);
        return NULL;
    }
    return answer;
}

#endif //COMPILER_2_0_INTERPRET_C