
VALUE *nodeToValue(NODE *node) {
    TOKEN *n = (TOKEN *) node;
    VALUE *endValue = malloc(sizeof(VALUE));

    if (n->type == CONSTANT) {
        endValue->type = 0;
        endValue->v.integer = n->value;
        return endValue;
    } else if (n->type == STRING_LITERAL) {
        endValue->type = 2;
        endValue->v.string = n->lexeme;
        return endValue;
    }

    free(endValue);
    return NULL;
}


TOKEN *addressToToken(VALUE *addressValue) {


    NODE *node = malloc(sizeof(NODE *));

    TOKEN *t = (TOKEN *) node;

    printf("inside: %s\n", t->lexeme);
    return t;
}



