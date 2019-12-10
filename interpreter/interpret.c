#ifndef COMPILER_2_0_INTERPRET_C
#define COMPILER_2_0_INTERPRET_C


#include <stddef.h>
#include <stdlib.h>

#include "interpreter/headers/value.h"
#include "Lexer_Parser_Files/nodes.h"
#include "Lexer_Parser_Files/C.tab.h"
#include "headers/environment.h"
#include "headers/bindings.h"
#include "headers/arithmetic.h"
#include "headers/apply.h"
#include "headers/closures.h"
#include "headers/debug.h"

// Prototypes.

VALUE *node_to_value(NODE *pNode);
VALUE *interpret_if(NODE* tree, ENV* e);
VALUE* function_definition(NODE* tree, ENV* e);
VALUE* sequence_method(NODE *tree, ENV *e);
VALUE *return_method(NODE *tree, ENV *e);
VALUE *declare(NODE *tree, ENV *e);

VALUE *interpret(NODE *tree, ENV *e) {

    if (tree == NULL) return NULL;

    switch(tree->type){
        case LEAF: return interpret(tree->left, e);
        case 'D': return function_definition(tree, e);
        case ';': return sequence_method(tree, e);
        case IDENTIFIER: return name_method((TOKEN *) tree, e->frames);
        case CONSTANT: // Use STRING_LITERAL case.
        case STRING_LITERAL: return node_to_value(tree);
        case RETURN: return return_method(tree, e);
        case '~': return declare(tree, e);
        case APPLY: return apply((TOKEN *) tree->left->left, tree->right, e);
        case IF: return interpret_if(tree, e);
        case '=': return assignment((TOKEN *) tree->left->left, e->frames, interpret(tree->right, e));
        case '+': return add_method(tree->left, tree->right, e);
        case '-': return subtract_method(tree->left, tree->right, e);
        case '*': return multiply_method(tree->left, tree->right, e);
        case '/': return divide_method(tree->left, tree->right, e);
        case GE_OP: return GE_OP_method(tree->left, tree->right, e);
        case LE_OP: return LE_OP_method(tree->left, tree->right, e);
        case NE_OP: return NE_OP_method(tree->left, tree->right, e);
        case EQ_OP: return EQ_OP_method(tree->left, tree->right, e);
        case '<': return LT_method(tree->left, tree->right, e);
        case '>': return GT_method(tree->left, tree->right, e);

    }

    return NULL;
}

VALUE *declare(NODE *tree, ENV *e) {
    if (tree->right->type == LEAF) declaration_method((TOKEN *) tree->right->left, e->frames); // For a closure declaration.
    else {
        declaration_method((TOKEN *) tree->right->left->left, e->frames);
        if (tree->right->type == '=') interpret(tree->right, e);
    }
    return NULL;
}

VALUE *return_method(NODE *tree, ENV *e) {
    VALUE* returnValue = interpret(tree->left, e);
    returnValue->return_answer = 1;
    return returnValue;
}

VALUE* sequence_method(NODE *tree, ENV *e) {
    VALUE* left = interpret(tree->left, e);
    if(left != NULL && left->return_answer == 1) return left;
    else free(left); return interpret(tree->right, e);
}

VALUE* function_definition(NODE* tree, ENV* e){
    if (tree->left->type == 'F') {
        return interpret(tree->right, e);
    }
    else {
        declaration_method((TOKEN *) tree->left->right->left->left, e->frames);
        assignment((TOKEN *) tree->left->right->left->left, e->frames, build_closure(e->frames, tree->left->right->right, tree->right));
        return NULL;
    }
}

VALUE *interpret_if(NODE* tree, ENV* e) {
    if(interpret(tree->left, e)->v.boolean == 1){
        if(tree->right->type != ELSE) return interpret(tree->right, e);
        else return interpret(tree->right->left, e);
    }
    else{
        if(tree->right->type != ELSE) return NULL;
        else return interpret(tree->right->right, e);
    }
}

VALUE *node_to_value(NODE *node) {

    if(node == NULL) return NULL;

    TOKEN *n = (TOKEN *) node;

    if (n->type == CONSTANT) return make_lint_value(n->value);
    else if (n->type == STRING_LITERAL) return make_string_value(n->lexeme);
    else error_exit_method("Node type invalid; cannot convert to value.");
}


#endif //COMPILER_2_0_INTERPRET_C