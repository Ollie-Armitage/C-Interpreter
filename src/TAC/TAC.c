#include <src/TAC/headers/TAC.h>

FILE* out;

char *make_temporary(int number);

void generate_assign(NODE *node, TAC **env);

void generate_arithmetic(NODE *node, TAC **env, char *type);

TAC *load_tac();

void generate_load(struct node *node, TAC **env);

TAC* generate(NODE* tree, TAC **env);

void generate_store(TOKEN *token, TAC **env);

char *get_current_temp(int offset);

TAC *new_tac(TAC **env, OP op);

char* make_new_temporary();

int temporary_num = 0;

int get_temporary_num(){
    return temporary_num;
};

void enumerate_temporary_num(){
    temporary_num++;
}

void load_values(NODE *node, TAC **env);

void generate_proc(NODE *node, TAC **tac);

void print_TAC(TAC* env){
    if(env->next != NULL) print_TAC((TAC *) env->next);

    if(env->op == eBLOCK) fprintf(out, "block %d\n", env->args.block.nvars);
    else if(env->op == ePROC) return;
    else if(env->op == eCALL) fprintf(out, "call %s %d\n", env->args.call.name->lexeme, env->args.call.arity);
    else if(env->op == eLOAD) {
        fprintf(out, "load %s ", env->args.load.t1);
        if(env->args.load.type == 0) fprintf(out, "%s\n", env->args.load.value.name->lexeme);
        else fprintf(out, "%d\n", env->args.load.value.constant);
    }
    else if(env->op == eMATH) fprintf(out, "%s %s %s %s\n", env->args.math.type, env->args.math.t1, env->args.math.t2, env->args.math.t3);
    else if(env->op == eSTORE) fprintf(out, "store %s %s\n", env->args.store.t1, env->args.store.name->lexeme);
}

void generate_TAC(NODE* tree, char* file_directory, int debug){
    TAC* tac = malloc(sizeof(TAC));
    out = fopen("TAC_OUT", "w");
    generate(tree, &tac);
    print_TAC(tac);
    fclose(out);

}

TAC* generate(NODE* tree, TAC **env){
    if(tree == NULL) return NULL;

    switch (tree->type) {
        case '~':
            generate(tree->right, env);
            break;
        case LEAF:
            generate(tree->left, env);
            break;
        case 'D':
            generate_proc(tree, env);
            generate(tree->right, env);
            break;
        case ';':
            generate(tree->left, env);
            generate(tree->right, env);
            break;
        case '=':
            generate_assign(tree, env);
            break;
        case RETURN:
            generate(tree->left, env);
            break;
    }
}

void generate_proc(NODE *node, TAC **tac) {

}


void generate_arithmetic(NODE *node, TAC **env, char *type) {
    load_values(node->left, env);
    load_values(node->right, env);
    new_tac(env, eMATH);
    (*env)->args.math.t1 = make_temporary(get_temporary_num() - 1);
    (*env)->args.math.t2 = make_temporary(get_temporary_num());
    (*env)->args.math.t3 = make_new_temporary();
    (*env)->args.math.type = type;
}

LOAD* build_load(int type, NODE* node, char *temporary){
    LOAD* load = malloc(sizeof(LOAD));
    load->type = type;
    if(type == 0) load->value.name = (TOKEN*)node;
    else if(type == 1) load->value.constant = ((TOKEN*)node)->value;
    else load->value.name = NULL;
    load->t1 = temporary;
    return load;
}

/* Loads should only be done on the right hand side of a statement.  */

void generate_load(NODE *node, TAC **env) {
    new_tac(env, eLOAD);
    if(node->type == IDENTIFIER){
        (*env)->args.load = *build_load(0, node, make_new_temporary());
    }
    else if(node->type == CONSTANT){
        (*env)->args.load = *build_load(1, node, make_new_temporary());
    }
    else{
        perror("Unknown node type for generating load.");
        exit(1);
    }
}

TOKEN* get_assign_name(NODE* node){
    if(node == NULL) return NULL;
    else if(node->type == LEAF || node->type == '=') return get_assign_name(node->left);
    else if(node->type == IDENTIFIER) return (TOKEN*)node;
    else perror("Unexpected node.");
    return NULL;
}

void generate_assign(NODE *node, TAC **env) {
    load_values(node, env);
    generate_store(get_assign_name(node), env);
}

void load_values(NODE *node, TAC **env) {
    if(node == NULL) return;
    else if(node->type == '=') return load_values(node->right, env);
    else if(node->type == LEAF) return load_values(node->left, env);
    else if(node->type == CONSTANT || node->type == IDENTIFIER) generate_load(node, env);
    else if(node->type == '+') generate_arithmetic(node, env, "add");
    else if(node->type == '-')  generate_arithmetic(node, env, "subtract");
    else if(node->type == '/') generate_arithmetic(node, env, "divide");
    else if(node->type == '*') generate_arithmetic(node, env, "multiply");
    else if(node->type == '%') generate_arithmetic(node, env, "mod");
    else perror("Unrecognized Node type.\n");
}

TAC *new_tac(TAC **env, OP op) {

    TAC* tac = malloc(sizeof(TAC));
    tac->op = op;
    tac->next = (struct TAC *) *env;
    *env = tac;
    return *env;
}

void generate_store(TOKEN *token, TAC **env) {
    new_tac(env, eSTORE);
    (*env)->args.store.name = token;
    (*env)->args.store.t1 = make_temporary(get_temporary_num());
}

char *make_temporary(int number) {
    char* temporary = malloc(sizeof(char*));
    sprintf(temporary, "t%d", number);
    return temporary;
}

char* make_new_temporary(){
    enumerate_temporary_num();
    char* temporary = make_temporary(get_temporary_num());
    return temporary;
}



