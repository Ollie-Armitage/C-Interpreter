VALUE *block_method(NODE *block, ENV *e);

VALUE *return_method(NODE *tree, ENV *e);

VALUE *interpret(NODE *tree, ENV *e) {
    if (tree == NULL) return NULL;
    if (tree->type == LEAF) { return interpret(tree->left, e); }
    else if (tree->type == INT || tree->type == FUNCTION || tree->type == VOID) {}
    else if (tree->type == IDENTIFIER) { return name_method((TOKEN *) tree, e->frames); }
    else if (tree->type == CONSTANT || tree->type == STRING_LITERAL) { return nodeToValue(tree); }
    else if (tree->type == RETURN) {
        VALUE *answer = return_method(tree->left, e);
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