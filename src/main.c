#include "main.h"


/* Linked parser variables. */

extern int yydebug;
extern NODE *yyparse(void);
extern NODE *ans;
extern FILE* yyin;
extern int yylex();
extern void init_symbtable(void);

/* build_AST Should take the input parameter of a specific file directory, and output the tree node. */

NODE *build_AST(char *file_directory) {
    if(file_directory != NULL){
        FILE *file;
        file = fopen(file_directory, "r");

        char* line = NULL;
        if(!file){
            printf("Cannot open file.\n");
            exit(1);
        }

        yyin = file;
        yylex();
        yyparse();
        printf("\n");

    }
    else yyparse();
    return ans;
}

int run(char* file_directory, int run_type, int test_mode) {

    ENV *e = malloc(sizeof(ENV));
    e->frames = malloc(sizeof(FRAME));
    NODE* tree;

    if(file_directory != NULL) tree = build_AST(file_directory);
    else tree = build_AST(NULL);


    print_tree(tree);

    switch(run_type){
        case TAC_TYPE:
        case MIPS_TYPE:
        case INTERPRETER_TYPE: interpreter(tree, e, file_directory, test_mode);
        default:
            free(e);
            return 0;
    }
}

int main(int argc, char **argv) {

    char *file_path = NULL, **program_args = NULL;
    if(argv[1] == NULL) printf("Entering lexer without preset file.\n");
    else{
        program_args = malloc(sizeof(char*) * argc - 2);
        file_path = argv[1];
        for(int i = 0; i < argc - 2; i++){
            program_args[i] = argv[i + 2];
        }
    }
    init_symbtable();
    printf("--C COMPILER\n");

    run(file_path, INTERPRETER_TYPE, TEST);
    return 0;
}
