#include <dirent.h>
#include "main.h"


/* Linked parser variables. */

extern int yydebug;

extern NODE *yyparse(void);

extern NODE *ans;
extern FILE *yyin;

extern int yylex();

extern void init_symbtable(void);

void check_and_record(char *path);

void run_tests();

void clean_file(char *filename);

int main(int argc, char **argv) {

    run_tests();

    init_symbtable();
    printf("--C COMPILER\n");

    FILE *results = fopen("results", "r");

    char ch;
    while ((ch = fgetc(results)) != EOF)
        printf("%c", ch);

    fclose(results);

    return 0;
}

void run_tests() {
    clean_file("results");
    DIR *dir;
    struct dirent *ent;
    char *directory_name = "tests/";
    if ((dir = opendir(directory_name)) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir(dir)) != NULL) {

            if (strcmp(ent->d_name, "CMakeLists.txt") != 0 && strcmp(ent->d_name, "..") != 0 &&
                strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "tests.c") != 0) {
                char *file_name = ent->d_name;
                char *file_path = malloc(strlen(file_name) + strlen(directory_name) + 1);
                strcat(file_path, directory_name);
                strcat(file_path, file_name);
                run(file_path, INTERPRETER_TYPE, 0, NULL);
                check_and_record(ent->d_name);
            }
        }
        closedir(dir);
    } else {
        /* could not open directory */
        printf("Could not open test directory.\n");
    }


}

/* build_AST Should take the input parameter of a specific file directory, and output the tree node. */

NODE *build_AST(char *file_directory) {
    if (file_directory != NULL) {
        FILE *file;
        file = fopen(file_directory, "r");

        char *line = NULL;
        if (!file) {
            printf("Cannot open file.\n");
            exit(1);
        }

        yyin = file;
        yylex();
        yyparse();
        printf("\n");
        fclose(file);

    } else yyparse();
    return ans;
}

int run(char* file_directory, int run_type, int number_of_args, char** args) {

    ENV *e = malloc(sizeof(ENV));
    e->frames = malloc(sizeof(FRAME));
    NODE* tree;

    if(file_directory != NULL){
        tree = build_AST(file_directory);
    } else{
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

void check_and_record(char *path) {
    char *directory_path = "tests/";
    char *real_path = malloc(strlen(path) + strlen(directory_path) + 1);
    strcat(real_path, directory_path);
    strcat(real_path, path);

    printf("Here: %s\n", real_path);

    char answer[BUFSIZ];
    char true_answer[BUFSIZ];
    FILE *f = fopen("temp", "r");
    fgets(answer, BUFSIZ, f);
    fclose(f);

    FILE *f2 = fopen(real_path, "r");

    if (f2 == NULL) {
        printf("Could not open '%s' in read", path);
        exit(1);
    }


    fgets(true_answer, BUFSIZ, f2);

    fclose(f2);

    FILE *test_results = fopen("results", "a");

    if (strcmp(answer, true_answer) == 0) fprintf(test_results, "Test Passed: %s\n", path);
    else fprintf(test_results, "Test Failed: %s\n", path);

    printf("\tExpected: %s", true_answer);
    printf("\tGot: %s", answer);
    printf("\n");

    free(real_path);
    fclose(test_results);
}

void clean_file(char *filename) {
    FILE *f = fopen(filename, "w");
    fclose(f);
}


