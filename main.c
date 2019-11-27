#include <Lexer_Parser_Files/nodes.h>
#include <interpreter/headers/environment.h>
#include <interpreter/interpret.c>
#include <interpreter/prints.c>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


extern int yydebug;

extern NODE *yyparse(void);

extern NODE *ans;

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
    freopen(fileDirectory, "r", stdin);
    yyparse();
    printf("\n");
    return ans;

}

// Interprets the tree built from the file in the directory, asserts something against the return of that.

void runScenario(char *fileDirectory) {
    NODE *tree = buildAST(fileDirectory);
    print_tree(tree);
    interpreter(tree);
}


int main(int argc, char **argv) {
    if (argc > 1 && strcmp(argv[1], "-d") == 0) yydebug = 1;

    init_symbtable();

    printf("--C COMPILER\n");

    runScenario("scenarios/literal_comparison.txt");

    return 0;
}
