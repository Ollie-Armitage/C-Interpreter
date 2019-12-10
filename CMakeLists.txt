cmake_minimum_required(VERSION 3.15)
project(Compiler_2_0)
set(CMAKE_C_STANDARD 11)
include_directories(.)

set(CMAKE_C_FLAGS  "-fprofile-arcs -ftest-coverage")

add_subdirectory(interpreter)
add_subdirectory(TAC)

add_executable(Compiler_2_0
        main.c
        test.c
        Lexer_Parser_Files/lex.yy.c
        Lexer_Parser_Files/C.tab.c
        Lexer_Parser_Files/nodes.c
        Lexer_Parser_Files/symbol_table.c)

target_link_libraries(Compiler_2_0 PUBLIC interpreter)
target_link_libraries(Compiler_2_0 PUBLIC TAC)


target_include_directories(Compiler_2_0 PUBLIC
        ${PROJECT_BINARY_DIR}
        ${PROJECT_SOURCE_DIR}/interpreter
        ${PROJECT_SOURCE_DIR}/TAC)
