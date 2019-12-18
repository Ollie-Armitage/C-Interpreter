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

int run(char* file_directory, int debug, int interpret,  int generate_tac, int generate_mc) {

    ENV *e = malloc(sizeof(ENV));
    e->frames = malloc(sizeof(FRAME));
    NODE* tree;

    if(file_directory != NULL) tree = build_AST(file_directory);
    else tree = build_AST(NULL);


    print_tree(tree);


    if(interpret) interpreter(tree, e, file_directory, debug);
    if(generate_tac) generate_TAC(tree, file_directory, debug);
    //if(generate_mc) generate_MC(tree, e, file_directory, debug);

}

void print_arg_usage(char **argv){
    printf("Usage: %s..\n\t -f <file_name> : file to be compiled\n", argv[0]);
    printf("\t -d : debug mode (run tests)\n");
    printf("\t -i : Interpretation Mode\n");
    printf("\t -t : Generate TAC code\n");
    printf("\t -m : Generate Machine code\n");
    exit(2);
}

int main(int argc, char **argv) {
    init_symbtable();
    int d_flag = 0, t_flag = 0, m_flag = 0, i_flag = 0;
    char* file_path = NULL;
    int opt;
    /* I will need flags for a) the input file, b) test mode c) generating TAC code d) generating machine code*/
    while((opt = getopt(argc, argv, "f:dtmi"))  != -1){
        switch(opt){
            case 'f':
                printf("File mode selected. (%s)\n", optarg);
                file_path = optarg;
                break;// file input flag
            case 'i':
                printf("Interpretation selected.\n");
                i_flag = 1;
                break;
            case 'd':
                printf("Debug mode selected.\n");
                d_flag = 1;
                break;// debug mode flag
            case 't':
                printf("TAC Generation selected.\n");
                t_flag = 1;
                break;// TAC code generation
            case 'm':
                printf("Machine Code generation selected.\n");
                m_flag = 1;
                break;// Machine code generation
            case '?':
                print_arg_usage(argv);
                break;
        }
    }
    printf("--C COMPILER\n");


    run(file_path, d_flag, i_flag, t_flag, m_flag);

    return 0;
}
