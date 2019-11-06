#include "interpreter/loadHeaders.c"

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

void runTest(char *fileDirectory) {
    NODE *tree = buildAST(fileDirectory);
    interpreter(tree);
}

// Run tests should run through the directory of all tests. (0 for interpreter, 1 for TAC, 2 for Machine code).

void runAllTests(int mode) {

    char *directory = NULL;

    if (mode == 0) {
        directory = "interpreter/Test_Files/straight-line/";
    } else if (mode == 1) {
        directory = "TAC/Test_Files/";
    } else {

    }

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

            strcat(directoryName, de->d_name);
            printf("%s", directoryName);

            runTest(directoryName);
        }
    }

    closedir(dr);


}


// BuildAST should use the directory name to read in an open file to yyparse,



int main(int argc, char **argv) {
    if (argc > 1 && strcmp(argv[1], "-d") == 0) yydebug = 1;

    init_symbtable();

    printf("--C COMPILER\n");

    runAllTests(0);


    printf("\nEvaluating tree...\n");


    return 0;
}
