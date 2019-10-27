VALUE *name_method(TOKEN *token, FRAME *frame) {
    while (frame != NULL) {
        BINDING *bindings = frame->bindings;
        while (bindings != NULL) {
            if (bindings->name == token) return bindings->val;
            bindings = (BINDING *) bindings->next;
        }

        frame = (FRAME *) frame->next;
    }
    printf("Unbound Variable: \"%s\"\n", token->lexeme);
}

VALUE *assignment(TOKEN *token, FRAME *frame, VALUE *value) {

    while (frame != NULL) {
        BINDING *bindings = frame->bindings;
        while (bindings != NULL) {
            if (bindings->name == token) bindings->val = value;
            return value;

        }
        frame = (FRAME *) frame->next;
    }
    printf("Assignment Failed.\n");
}

VALUE *declaration_method(TOKEN *token, FRAME *frame) {
    BINDING *bindings = frame->bindings;
    BINDING *new = malloc(sizeof(BINDING));
    if (new != 0) {
        new->name = token;
        new->val = NULL;
        new->next = (struct BINDING *) bindings;
        frame->bindings = new;
        return NULL;
    }
    printf("Binding Allocation Failed.\n");

}