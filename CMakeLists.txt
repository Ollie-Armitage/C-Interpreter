cmake_minimum_required(VERSION 3.15)
project(Compiler_2_0)
set(CMAKE_C_STANDARD 11)
include_directories(.)

set(CMAKE_C_FLAGS  "-fprofile-arcs -ftest-coverage -lcheck")

add_subdirectory(src)
add_subdirectory(tests)
target_link_libraries(interpreter_files)

add_executable(Compiler_2_0
        src/main.c
        src/interpreter/debug.c
        src/interpreter/interpret.c
        src/interpreter/value.c
        src/interpreter/arithmetic.c
        Lexer_Parser_Files/lex.yy.c
        Lexer_Parser_Files/C.tab.c
        Lexer_Parser_Files/nodes.c
        Lexer_Parser_Files/symbol_table.c)

