#include <src/TAC/headers/TAC.h>

FILE* out;

char *make_temporary(int number);

void generate_assign(NODE *node, TAC **env);

void generate_arithmetic(NODE *node, TAC **env, char *type);

BLOCK* build_block(int nvars);

void generate_load(struct node *node, TAC **env);

TAC* generate(NODE* tree, TAC **env);

LOAD* build_load(int type, NODE* node, char *temporary);

void generate_store(TOKEN *token, TAC **env);

TAC *new_tac(TAC **env, OP op);

CALL* build_call(TOKEN* name, int arity);

char* make_new_temporary();

int temporary_num = 0;

int get_temporary_num(){
    return temporary_num;
};

void enumerate_temporary_num(){
    temporary_num++;
}

TOKEN* get_assign_name(NODE* node);

void load_values(NODE *node, TAC **env);

void generate_proc(NODE *node, TAC **env);

void generate_block(NODE *node, TAC **env);

void generate_call(NODE *node, TAC **env);

void generate_arity_load(NODE *node, TAC **env, int count);

void generate_return(NODE *node, TAC **env);

void generate_end_block(TAC **env);

void print_TAC(TAC* env){
    if(env->next != NULL) print_TAC((TAC *) env->next);

    if(env->op == eBLOCK) fprintf(out, "block %d\n", env->args.block.nvars);
    else if(env->op == ePROC) fprintf(out, "proc %s ()\n", env->args.proc.name->lexeme);
    else if(env->op == eCALL) fprintf(out, "call %s %d\n", env->args.call.name->lexeme, env->args.call.arity);
    else if(env->op == eLOAD) {
        fprintf(out, "load %s ", env->args.load.t1);
        if(env->args.load.type == 0) fprintf(out, "%s\n", env->args.load.value.name->lexeme);
        else fprintf(out, "%d\n", env->args.load.value.constant);
    }
    else if(env->op == eRET) {
        if(env->args.ret.type == 0) fprintf(out, "return %s\n", env->args.ret.value.name->lexeme);
        else if(env->args.ret.type == 1) fprintf(out, "return %d\n", env->args.ret.value.constant);
        else fprintf(out, "return %s\n", env->args.ret.value.temporary);
    }
    else if(env->op == eMATH) fprintf(out, "%s %s %s %s\n", env->args.math.type, env->args.math.t1, env->args.math.t2, env->args.math.t3);
    else if(env->op == eSTORE) fprintf(out, "store %s %s\n", env->args.store.t1, env->args.store.name->lexeme);
    else if(env->op == eEND) fprintf(out, "end%s\n", env->args.end.type);
}

void generate_TAC(NODE* tree, char* file_directory, int debug){
    TAC* tac = malloc(sizeof(TAC));
    out = fopen("TAC_OUT", "w");
    generate(tree, &tac);
    print_TAC(tac);
    fclose(out);

}

TAC* generate(NODE* tree, TAC **env) {
    if (tree == NULL) return NULL;

    switch (tree->type) {
        case '~':
            generate(tree->right, env);
            break;
        case LEAF:
            generate(tree->left, env);
            break;
        case 'D':
            generate_proc(tree, env);
            break;
        case ';':
            generate(tree->left, env);
            generate(tree->right, env);
            break;
        case '=':
            generate_assign(tree, env);
            break;
        case RETURN:
            generate_return(tree, env);
            break;
        case APPLY:
            generate_call(tree, env);
            break;
    }
}

void generate_return(NODE* node, TAC** env){

    if(node->left->left->type == IDENTIFIER){
        new_tac(env, eRET);
        (*env)->args.ret.type = 0;
        (*env)->args.ret.value.name = (TOKEN*)node->left->left;
        return;
    }
    else if(node->left->left->type == CONSTANT){
        new_tac(env, eRET);
        (*env)->args.ret.type = 1;
        (*env)->args.ret.value.constant = ((TOKEN*)node)->value;
        return;
    }

    load_values(node, env);
    new_tac(env, eRET);
    (*env)->args.ret.type = 2;
    (*env)->args.ret.value.temporary = make_temporary(get_temporary_num());
}

RET* build_return(int type, NODE* node, TAC **env){
    RET* ret = malloc(sizeof(RET));

    if(type == IDENTIFIER){
        ret->type = 0;
        ret->value.name = get_assign_name(node);
    }
    else if(type == CONSTANT){
        ret->type = 1;
    }
    else {
        ret->type = 2;
        new_tac(env, eLOAD);
        load_values(node, env);
        ret->value.temporary = (*env)->args.math.t3;
    }

    return ret;
}

int call_arity(NODE* node, TAC** env, int count) {
    if (node == NULL) return count;
    else if (node->type == APPLY) count = call_arity(node->right, env, count);
    else if (node->type == ',') {
        count = call_arity(node->right, env, call_arity(node->left, env, count));
    }
    else if(node->type == LEAF) count = call_arity(node->left, env, count);
    else if(node->type == IDENTIFIER || node->type == CONSTANT){
        generate_arity_load(node, env, count);
        count = count + 1;
        return count;
    }
    else{
        perror("Unrecognised node in call_arity\n");
        exit(1);
    }
    return count;
}

char* make_new_arg(count){
    char* string = malloc(sizeof(char));
    sprintf(string, "a%d", count);
    return string;
}

void generate_arity_load(NODE *node, TAC **env, int count) {
    new_tac(env, eLOAD);
    if(node->type == IDENTIFIER){
        (*env)->args.load = *build_load(0, node, make_new_arg(count));
    }
    else if(node->type == CONSTANT){
        (*env)->args.load = *build_load(1, node, make_new_arg(count));
    }
    else{
        perror("Unknown node type for generating load.");
        exit(1);
    }
}

void generate_call(NODE *node, TAC **env) {
    if(node == NULL) return;
    else if(node->type == APPLY){
        int arity = call_arity(node, env, 1) - 1;
        new_tac(env, eCALL);
        (*env)->args.call = *build_call(get_assign_name(node->left), arity);
    }
}

void generate_block(NODE *node, TAC **env) {
    if(node == NULL) return;
    else if(node->type == 'D'){
        new_tac(env, eBLOCK);
        (*env)->args.block = *build_block(0);
    }

    generate(node->right, env);

    new_tac(env, eEND);
    (*env)->args.end.type = malloc(sizeof(char));
    (*env)->args.end.type = "block";


}

CALL* build_call(TOKEN* name, int arity){
    CALL* call = malloc(sizeof(CALL));
    call->name = name;
    call->arity = arity;
    return call;
}

BLOCK* build_block(int nvars){
    BLOCK* block = malloc(sizeof(BLOCK));
    block->nvars = nvars;
    return block;
}

PROC* build_procedure(TOKEN* name){
    PROC* proc = malloc(sizeof(PROC));
    proc->name = name;
    return proc;
}

void generate_proc(NODE *node, TAC **env) {
    if(node == NULL) return;
    else if(node->type == 'D'){ new_tac(env, ePROC); generate_proc(node->left, env); }
    else if(node->type == 'd') return generate_proc(node->left, env);
    else if(node->type == 'F'){ (*env)->args.proc = *build_procedure(get_assign_name(node->left)); return; }
    else{
        perror("Unrecognised Node type building procedure.");
        exit(1);
    }
    generate_block(node, env);

    new_tac(env, eEND);

    (*env)->args.end.type = malloc(sizeof(char));
    (*env)->args.end.type = "proc";
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
    else if(node->type == RETURN) return load_values(node->left, env);
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



