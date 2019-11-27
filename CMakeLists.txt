cmake_minimum_required(VERSION 3.15)
project(Compiler_2_0)
set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Compiler_2_0
        Lexer_Parser_Files/C.tab.c
        Lexer_Parser_Files/lex.yy.c
        Lexer_Parser_Files/nodes.c
        Lexer_Parser_Files/symbol_table.c
        main.c interpreter/arithmetic_tests.c interpreter/headers/arithmetic.h interpreter/headers/bindings.h interpreter/headers/closures.h interpreter/headers/interpret.h interpreter/headers/prints.h)


