#ifndef COMPILER_2_0_INTERPRET_C
#define COMPILER_2_0_INTERPRET_C


#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <interpreter/headers/value.h>

#include "headers/value.h"
#include "Lexer_Parser_Files/nodes.h"
#include "headers/environment.h"
#include "headers/bindings.h"
#include "headers/arithmetic.h"
#include "headers/apply.h"

#include "Lexer_Parser_Files/C.tab.h"

VALUE *node_to_value(NODE *pNode);

VALUE *return_method(struct node *tree, ENV *e);

VALUE *block_method(struct node *block, ENV *e);

VALUE *interpret(NODE *tree, ENV *e) {
    if (tree == NULL) return NULL;
    if (tree->type == LEAF) { return interpret(tree->left, e); }
    else if(tree->type == 'D'){ interpret(tree->left, e); return interpret(tree->right, e);}
    else if(tree->type == ';'){ interpret(tree->left, e); return interpret(tree->right, e);}
    else if(tree->type == 'F'){ return interpret(tree->left, e);}
    else if (tree->type == INT || tree->type == FUNCTION || tree->type == VOID) {}
    else if (tree->type == IDENTIFIER) { return name_method((TOKEN *) tree, e->frames); }
    else if (tree->type == CONSTANT || tree->type == STRING_LITERAL) { return node_to_value(tree); }
    else if (tree->type == RETURN) {
        return return_method(tree->left, e);}
    else if (tree->type == '~') {
        if (tree->right->type == LEAF) declaration_method((TOKEN *) tree->right->left, e->frames);
        else declaration_method((TOKEN *) tree->right->left->left, e->frames);
        return interpret(tree->right, e);
    } else if (tree->type == APPLY) {
        return apply((TOKEN*)tree->left->left, interpret(tree->right, e)); }
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
    else{
        return interpret(tree->left, e);
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