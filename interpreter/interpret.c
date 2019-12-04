#ifndef COMPILER_2_0_INTERPRET_C
#define COMPILER_2_0_INTERPRET_C


#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include "Lexer_Parser_Files/nodes.h"
#include "headers/environment.h"
#include "headers/bindings.h"
#include "headers/arithmetic.h"
#include "headers/apply.h"
#include "headers/closures.h"

#include "Lexer_Parser_Files/C.tab.h"

VALUE *node_to_value(NODE *pNode);

VALUE *return_method(struct node *tree, ENV *e);

VALUE *interpret_if(NODE* tree, ENV* e);

VALUE *interpret(NODE *tree, ENV *e) {
    if (tree == NULL) return NULL;
    if (tree->type == LEAF) { return interpret(tree->left, e); }
    else if (tree->type == 'D') {

        if (tree->left->type == 'F') {
            interpret(tree->left, e);
            return interpret(tree->right, e);
        }
        else {
            declaration_method((TOKEN *) tree->left->right->left->left, e->frames);
            assignment((TOKEN *) tree->left->right->left->left, e->frames,
                       build_closure(e->frames, tree->left->right->right, tree->right));
        }

    } else if (tree->type == ';') {

        while (tree->right->type == ';') {
            interpret(tree->left, e);
            tree = tree->right;
        }

        interpret(tree->left, e);
        return interpret(tree->right, e);

    } else if (tree->type == INT || tree->type == FUNCTION || tree->type == VOID) {}
    else if (tree->type == IDENTIFIER) { return name_method((TOKEN *) tree, e->frames); }
    else if (tree->type == CONSTANT || tree->type == STRING_LITERAL) { return node_to_value(tree); }
    else if (tree->type == RETURN) {
        return return_method(tree->left, e);
    } // TODO:
    else if (tree->type == '~') {
        if (tree->right->type == LEAF) {
            declaration_method((TOKEN *) tree->right->left, e->frames);
        } // For a closure declaration.
        else {
            declaration_method((TOKEN *) tree->right->left->left, e->frames);
            if (tree->right->type == '=') interpret(tree->right, e);
        } // For a variable's declaration, and if necessary assignment.
    } else if (tree->type == APPLY) { return apply((TOKEN *) tree->left->left, tree->right, e); }
    else if (tree->type == IF) { return interpret_if(tree, e); }
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

}

VALUE *interpret_if(NODE* tree, ENV* e) {
    if(interpret(tree->left, e)->v.boolean == 1){

        if(tree->right->type != ELSE){
            return interpret(tree->right, e);
        }
        else{
            return interpret(tree->right->left, e);
        }

    }
    else{
        if(tree->right->type != ELSE){
            return NULL;
        }
        else{
            return interpret(tree->right->right, e);
        }
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


VALUE *return_method(NODE *tree, ENV *e) {
    VALUE *answer = interpret(tree, e);
    return answer;
}

#endif //COMPILER_2_0_INTERPRET_C