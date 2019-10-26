#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Lexer_Parser_Files/nodes.h"
#include <Lexer_Parser_Files/C.tab.h>
#include "types/value.h"
#include "types/environment.h"
#include "interpreter/value.c"
#include "interpreter/conversions.c"
#include "interpreter/bindings.c"
#include "interpreter/arithmetic.c"
#include "interpreter/interpret.c"
#include "TAC/TAC.h"
#include "TAC/TAC.c"
#include "interpreter/prints.c"

#include "Google_Tests/interpreter/interpreterTest.c"


extern int yydebug;

extern NODE *yyparse(void);

extern NODE *ans;

extern void init_symbtable(void);

void interpreter(NODE *node) {
    ENV *e = malloc(sizeof(ENV *));
    e->frames = malloc(sizeof(FRAME));
    block_method(node, e);
}

int main(int argc, char **argv) {
    NODE *tree;
    if (argc > 1 && strcmp(argv[1], "-d") == 0) yydebug = 1;
    init_symbtable();
    printf("--C COMPILER\n");
    freopen("Google_Tests/Test_Files/straight-line/literal.txt", "r", stdin);
    yyparse();

    tree = ans;
    printf("parse finished with %p\n", tree);
    print_tree(tree);

    printf("\nEvaluating tree...\n");

    interpreter(tree);
    tacGenerator(tree);
    testLiteral();

    return 0;
}
