#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include "Lexer_Parser_Files/nodes.h"
#include "Lexer_Parser_Files/C.tab.h"
#include "interpreter/types/value.h"
#include "interpreter/types/environment.h"
#include "interpreter/value.c"
#include "interpreter/conversions.c"
#include "interpreter/bindings.c"
#include "interpreter/arithmetic.c"
#include "interpreter/interpret.c"
#include "TAC/TAC.h"
#include "TAC/TAC.c"
#include "interpreter/prints.c"


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

NODE* buildAST(){

    NODE* tree;
    init_symbtable();

    const char *directory = "interpreter/Test_Files/straight-line/";

    struct dirent *de;
    DIR *dr = opendir(directory);

    if (dr == NULL) {
        printf("Could not open current directory");
    }

    while ((de = readdir(dr)) != NULL) {

        if(!strcmp(de->d_name, ".") || !strcmp(de->d_name, "..")){

        }
        else{

            char *directoryName = (char *) malloc(strlen(directory) + strlen(de->d_name) + 1);
            strcat(directoryName, directory);
            printf("%s", directoryName);

            strcat(directoryName, de->d_name);

            printf("\n");
            freopen(directoryName, "r", stdin);
            yyparse();
            printf("\n");

            tree = ans;
        }
    }

    closedir(dr);


    return tree;
}

int main(int argc, char **argv) {
    if (argc > 1 && strcmp(argv[1], "-d") == 0) yydebug = 1;

    printf("--C COMPILER\n");

    NODE* tree = buildAST();


    printf("\nEvaluating tree...\n");

    interpreter(tree);
    tacGenerator(tree);


    return 0;
}
