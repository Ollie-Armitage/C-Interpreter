#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "interpreter/headers/interpret.h"
#include "interpreter/headers/environment.h"
#include "interpreter/headers/debug.h"
#include "TAC/TAC.h"
#include "Lexer_Parser_Files/nodes.h"


/* Linked parser variables. */

extern int yydebug;
extern NODE *yyparse(void);
extern NODE *ans;
extern FILE* yyin;
extern int yylex();
extern void init_symbtable(void);

void bad_args_error() {
    printf("Please run program in the format: <Program> <File> <FileArgs1> <FileArgs2> ...\n");
    exit(1);
}

/* build_AST Should take the input parameter of a specific file directory, and output the tree node. */

NODE *build_AST(char *file_directory) {
    if(file_directory != NULL){
        FILE *file;
        file = fopen(file_directory, "r");

        char* line = NULL;
        if(!file){
            printf("Cannot open file.\n");
            bad_args_error();
        }

        yyin = file;
        yylex();
        yyparse();
        printf("\n");

    }
    else yyparse();
    return ans;
}

int run(char* file_directory, int run_type, int number_of_args, char** args) {

    ENV *e = malloc(sizeof(ENV));
    e->frames = malloc(sizeof(FRAME));
    NODE* tree;

    if(file_directory != NULL){
        tree = build_AST(file_directory);
    }
    else{
        tree = build_AST(NULL);
    }

    print_tree(tree);

    if(run_type == 0){
        interpreter(tree, e, number_of_args, args);
    }
    else if(run_type == 1){
        three_address_code(tree);
    }


    free(e->frames);
    free(e);

    return 1;
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

    run(file_path, 0, argc - 2, program_args);
    return 0;
}
