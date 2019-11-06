FRAME *extend_frame(FRAME *env, NODE *ids, NODE *args) {
    NODE *ip;
    NODE *ap;

    FRAME *newEnv = malloc(sizeof(FRAME));
    if (newEnv == 0) {
        printf("Frame Allocation Failed.\n ");
        return NULL;
    }
    newEnv->bindings = NULL;

    // For the sequence of identifiers and the sequence of arguments, while neither of them are equal to null, work through them.


    for (ip = ids; ip != NULL; ip = ip->right) {
        for (ap = args; ap != NULL; ap = ap->right) {
            BINDING *new = malloc(sizeof(BINDING));

            if (new != 0) {
                new->name = (TOKEN *) ip->left;
            }

        }
    }
}
