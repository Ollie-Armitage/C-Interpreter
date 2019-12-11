
#ifndef COMPILER_2_0_MAIN_H
#define COMPILER_2_0_MAIN_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "interpreter/headers/interpret.h"
#include "interpreter/headers/environment.h"
#include "interpreter/headers/debug.h"
#include "Lexer_Parser_Files/nodes.h"

int run(char* file_directory, int run_type, int number_of_args, char** args);
NODE *build_AST(char *file_directory);

#define INTERPRETER_TYPE 0
#define TAC_TYPE 1
#define MIPS_TYPE 2

#endif //COMPILER_2_0_MAIN_H
