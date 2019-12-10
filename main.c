#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>

#include "interpreter/headers/interpret.h"
#include "interpreter/headers/environment.h"
#include "interpreter/headers/debug.h"
#include "TAC/TAC.h"
#include "Lexer_Parser_Files/nodes.h"

#include <interpreter/headers/bindings.h>

// Linked parser variables.

extern int yydebug;
extern NODE *yyparse(void);
extern NODE *ans;
extern FILE* yyin;
extern int yylex();
extern void init_symbtable(void);

// buildAST Should take the input parameter of a specific file directory, and output the tree node.

NODE *buildAST(char *fileDirectory) {

    printf("\n");

    if(fileDirectory != NULL){
        FILE *file;
        file = fopen(fileDirectory, "r");

        char* line = NULL;
        if(!file){
            printf("Can't open file.");
        }

        yyin = file;
        yylex();
        yyparse();
        printf("\n");

    }
    else{
        yyparse();
    }

    return ans;

}

int run(char* fileDirectory, int runType, int numberOfArgs, char** args) {

    ENV *e = malloc(sizeof(ENV));
    e->frames = malloc(sizeof(FRAME));
    NODE* tree;

    if(fileDirectory != NULL){
        tree = buildAST(fileDirectory);
    }
    else{
        tree = buildAST(NULL);
    }

    print_tree(tree);

    if(runType == 0){
        interpreter(tree, e, numberOfArgs, args);
    }
    else if(runType == 1){
        ThreeAddressCode(tree);
    }


    free(e->frames);
    free(e);

    return 1;
}



int main(int argc, char **argv) {

    char *file_path = NULL;
    char **programArgs = malloc(sizeof(char*)*argc - 2);
    if(argv[1] == NULL){ printf("Entering lexer without preset file.\n"); }
    else{
        file_path = argv[1];
        for(int i = 0; i < argc - 2; i++){
            programArgs[i] = argv[i+2];
        }
    }

    init_symbtable();

    printf("--C COMPILER\n");

    run(file_path, 0, argc - 2, programArgs);
    return 0;
}
