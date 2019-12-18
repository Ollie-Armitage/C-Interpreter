//
// Created by ollie on 17/12/2019.
//


#include <src/TAC/headers/TAC.h>


TAC *generate(NODE *tree, BB *basic_block);

void *load_name(NODE *node, TAC* tac);

void load_constant(NODE *node, TAC* tac);

int generate_TAC(NODE *tree, char* file_directory, int debug){
    BB* basic_block = malloc(sizeof(BB));
    TAC* tac = malloc(sizeof(TAC));
    tac->tac_number = 0;
    basic_block->leader = tac;
    generate(tree, basic_block);
    return 0;
}

TAC *generate(NODE *tree, BB *basic_block) {
    printf("hi\n");
    if(tree == NULL) return NULL;

    switch(tree->type){
        case LEAF:
            return generate(tree->left, basic_block);
        case IDENTIFIER:
            load_name(tree, basic_block->leader);
            break;
        case CONSTANT: /* Use STRING_LITERAL case. */
            load_constant(tree, basic_block->leader);
            break;
        default:
            generate(tree->left, basic_block);
            generate(tree->right, basic_block);
    }
    return NULL;
}

void load_constant(NODE *node, TAC* tac) {
    tac->args.load.value.constant = ((TOKEN*)node)->value;
    printf("load t%d %d\n", tac->tac_number, ((TOKEN*)node)->value);
}

void *load_name(NODE *node, TAC* tac) {
    tac->args.load.value.variable = (TOKEN *) node;
}

TAC* generate_instruction(enum OP *op, TOKEN* arg1, TOKEN* arg2, TOKEN* result){
    TAC* tac = malloc(sizeof(TAC));
    tac->op = op;
    tac->result = result;
    return tac;
}


