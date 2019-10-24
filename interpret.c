#include <Lexer_Parser_Files/C.tab.h>

VALUE *nodeToValue(NODE *node);

VALUE *block_method(NODE *block, ENV *e);

VALUE *return_method(NODE *expression, ENV *e);

VALUE *interpret(NODE *tree, ENV *e) {
    if (tree == NULL) return NULL;
    if (tree->type == LEAF) { return interpret(tree->left, e); }
    else if (tree->type == INT || tree->type == FUNCTION || tree->type == VOID) {}
    else if (tree->type == IDENTIFIER) { return name_method((TOKEN *) tree, e->frames); }
    else if (tree->type == CONSTANT || tree->type == STRING_LITERAL) { return nodeToValue(tree); }
    else if (tree->type == RETURN) { return_method(tree->left, e); }
    else if (tree->type == '~') {}
    else if (tree->type == '=') {}
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


VALUE *block_method(NODE *block, ENV *e) {
    while (block != NULL) {
        interpret(block, e);
        block = block->right;
    }
}

VALUE *return_method(NODE *expression, ENV *e) {
    VALUE *answer = interpret(expression, e);
    if (answer->type == 0) {
        printf("%d\n", answer->v.integer);
    } else if (answer->type == 1) {
        if (answer->v.boolean == 0) {
            printf("False\n");
        } else if (answer->v.boolean == 1) {
            printf("True\n");
        }
    } else if (answer->type == 2) {
        printf("%s", answer->v.string);
    } else {
        printf("No valid return type.");
    }
    return interpret(expression, e);
}