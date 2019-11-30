#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "interpreter/headers/interpret.h"
#include "interpreter/headers/environment.h"
#include "interpreter/headers/prints.h"
#include "Lexer_Parser_Files/nodes.h"


extern int yydebug;

extern NODE *yyparse(void);

extern NODE *ans;

extern FILE* yyin;
extern int yylex();

extern void init_symbtable(void);

void interpreter(NODE *node) {
    ENV *e = malloc(sizeof(ENV));
    e->frames = malloc(sizeof(FRAME));
    block_method(node, e);
    free(e->frames);
    free(e);
}

// buildAST Should take the input parameter of a specific file directory, and output the tree node.

NODE *buildAST(char *fileDirectory) {

    printf("\n");

    FILE *file;
    file = fopen(fileDirectory, "r");
    ssize_t read;
    size_t len = 0;
    char* line = NULL;
    if(!file){
        printf("Can't open file.");
    }

    yyin = file;


    yylex();
    yyparse();

    printf("\n");
    return ans;

}

// Interprets the tree built from the file in the directory, asserts something against the return of that.

void interpret_file(char *fileDirectory) {


    NODE *tree = buildAST(fileDirectory); // Causing scanf issue.

    print_tree(tree);
    interpreter(tree);
}


int main(int argc, char **argv) {
    if (argc > 1 && strcmp(argv[1], "-d") == 0) yydebug = 1;



    init_symbtable();

    printf("--C COMPILER\n");
    interpret_file("tests/literal_read_int");

    return 0;
}
