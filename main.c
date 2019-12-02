#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <interpreter/headers/value.h>
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

int run_tests(){
    FILE* file = fopen("tests.log", "w");
    DIR *folder;
    struct dirent *dr;
    char* test_directory = "tests/";

    folder = opendir(test_directory);
    if(folder == NULL)
    {
        puts("Unable to read tests directory");
        return(1);
    }

    while( (dr = readdir(folder)) != NULL)
    {
        if(strcmp(dr->d_name, ".." ) != 0 && strcmp(dr->d_name, ".") != 0){
            char* file_name = dr->d_name;
            char* file_path = malloc(sizeof(char));
            strcat(file_path, test_directory);
            strcat(file_path, dr->d_name);

            if(interpreter(file_path)) fprintf(file, "Test Passed: %s\n", file_name); else fprintf(file, "Test Failed: %s\n", file_name);
            free(file_path);
        }
    }

    fclose(file);
    closedir(folder);

    file = fopen("tests.log", "r");
    char buffer[255];

    while(fgets(buffer, 255, (FILE*)file)){
        printf("%s", buffer);
    }

    fclose(file);
}

int main(int argc, char **argv) {
    if (argc > 1 && strcmp(argv[1], "-d") == 0) yydebug = 1;
    init_symbtable();

    printf("--C COMPILER\n");


    run_tests();


    return 0;
}
