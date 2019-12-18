#include <src/TAC/headers/TAC.h>

FILE* out;

void generate_func_def(NODE *node);

INS* make_instruction(label l, i_type type);

INS* make_param_instruction(INS* instruction);

INS* make_quad_instruction(INS* instruction);

INS* make_jump_instruction(INS* instruction);

BLOCK* make_block(NODE* node);

INS* generate_assignment(NODE *node);

void generate_TAC(NODE* tree, char* file_directory, int debug){
    out = fopen("TAC_OUT", "w");
    generate(tree);
    fclose(out);
}

INS* generate(NODE* tree){

    if(tree == NULL) return NULL;

    switch(tree->type){
        case 'D':
            generate_func_def(tree);
            break;
        case 'd':
        case 'F':
        /* Ins from book. */
        case '=':
            generate_assignment(tree);
        default: break;
    }

    return NULL;
}

INS* generate_assignment(NODE *node) {
    INS* instruction = malloc(sizeof(INS));
    instruction->val.copy.arg1 = ;
}

void generate_func_def(NODE *node) {
    if(node->left->type == 'F') printf("proc %s\n", ((TOKEN*)node->left->left->left)->lexeme);
    else printf("proc %s\n", ((TOKEN*)node->left->left->left->left)->lexeme);


    BLOCK* block = make_block(node->right);

    printf("endproc");
}



BLOCK* make_block(NODE* node){
    BLOCK* block = malloc(sizeof(BLOCK));
    return block;
}

INS* make_instruction(label l, i_type type){
    INS* instruction = malloc(sizeof(INS));
    instruction->type = type;

    switch(instruction->type){
        case PARAM:
            instruction = make_param_instruction(instruction);
        case QUAD:
            instruction = make_quad_instruction(instruction);
        case JUMP:
            instruction = make_jump_instruction(instruction);

    }

    return instruction;
}

INS* make_quad_instruction(INS* instruction) {
    return instruction;
}

INS* make_param_instruction(INS* instruction) {
    return instruction;
}

INS* make_jump_instruction(INS* instruction){
    return instruction;
}

