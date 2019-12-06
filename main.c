#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>

#include "interpreter/headers/interpret.h"
#include "interpreter/headers/environment.h"
#include "interpreter/headers/prints.h"
#include "Lexer_Parser_Files/nodes.h"

#include <interpreter/headers/bindings.h>
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

int interpreter(char* fileDirectory) {

    ENV *e = malloc(sizeof(ENV));
    e->frames = malloc(sizeof(FRAME));
    VALUE* answer;
    NODE* tree;

    if(fileDirectory != NULL){
        tree = buildAST(fileDirectory);
    }
    else{
        tree = buildAST(NULL);
    }

    print_tree(tree);
    answer = interpret(tree, e);

    return 1;

}

int main(int argc, char **argv) {
    if (argc > 1 && strcmp(argv[1], "-d") == 0) yydebug = 1;
    init_symbtable();

    printf("--C COMPILER\n");

    interpreter("tests/twice");

    return 0;
}
