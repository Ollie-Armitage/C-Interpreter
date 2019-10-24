#include <stdio.h>
#include <stdlib.h>
#include "Lexer_Parser_Files/nodes.h"
#include <Lexer_Parser_Files/C.tab.h>
#include <string.h>

#include "types/value.h"
#include "types/environment.h"

#include "value.c"
#include "conversions.c"
#include "bindings.c"
#include "arithmetic.c"
#include "interpret.c"

#include "prints.c"


extern int yydebug;

extern NODE *yyparse(void);

extern NODE *ans;

extern void init_symbtable(void);

int main(int argc, char **argv) {
    ENV *e = malloc(sizeof(ENV *));
    NODE *tree;
    if (argc > 1 && strcmp(argv[1], "-d") == 0) yydebug = 1;
    init_symbtable();
    printf("--C COMPILER\n");
    freopen("testFiles/straight-line/literal.txt", "r", stdin);
    yyparse();

    tree = ans;
    printf("parse finished with %p\n", tree);
    print_tree(tree);


    printf("Press any key to continue.\n");

    printf("\nEvaluating tree...\n");
    interpret(tree, e);

    return 0;
}
