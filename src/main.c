#include "main.h"


/* Linked parser variables. */

extern int yydebug;
extern NODE *yyparse(void);
extern NODE *ans;
extern FILE* yyin;
extern int yylex();
extern void init_symbtable(void);

void clean_files();

void check_and_record(char *path);

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

    switch(run_type){
        case TAC_TYPE:
        case MIPS_TYPE:
        case INTERPRETER_TYPE: interpreter(tree, e, number_of_args, args);
        default:
            free(e->frames);
            free(e);
            return 0;
    }
}

int main(int argc, char **argv) {

    clean_files();

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

    run(file_path, INTERPRETER_TYPE, argc - 2, program_args);

    check_and_record(file_path);

    FILE* results = fopen("results", "r");

    char ch;
    while((ch = fgetc(results)) != EOF)
        printf("%c", ch);

    fclose(results);

    return 0;
}

void check_and_record(char *path) {
    char answer[BUFSIZ];
    char true_answer[BUFSIZ];
    FILE *f = fopen("temp", "r");
    fgets(answer, BUFSIZ, f);
    fclose(f);

    FILE *f2 = fopen(path, "r");

    fgets(true_answer, BUFSIZ, f2);

    fclose(f2);

    FILE* test_results = fopen("results", "a");

    if(strcmp(answer, true_answer) == 0) fprintf(test_results, "Test Passed: %s\n", path);
    else fprintf(test_results, "Test Failed: %s\n", path);

    fclose(test_results);


}

void clean_files() {
    FILE* f = fopen("temp", "w");
    fclose(f);
    f = fopen("results", "w");
    fclose(f);
}
