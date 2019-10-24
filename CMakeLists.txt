cmake_minimum_required(VERSION 3.15)
project(Compiler_2_0 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(Header_Files)
include_directories(Lexer_Parser_Files)
include_directories(types)

add_executable(Compiler_2_0
        Header_Files/arithmetic.h
        Header_Files/main.h
        Lexer_Parser_Files/C.tab.c
        Lexer_Parser_Files/C.tab.h
        Lexer_Parser_Files/lex.yy.c
        Lexer_Parser_Files/nodes.c
        Lexer_Parser_Files/nodes.h
        Lexer_Parser_Files/symbol_table.c
        Lexer_Parser_Files/token.h
        types/environment.h
        types/value.h
        main.c)
