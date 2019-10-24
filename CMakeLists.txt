cmake_minimum_required(VERSION 3.15)
project(Compiler_2_0)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(testFiles)
include_directories(testFiles/straight-line)

add_executable(Compiler_2_0
        testFiles/straight-line/function.txt
        testFiles/straight-line/functionVariableDeclaration.txt
        testFiles/straight-line/literal.txt
        testFiles/straight-line/literalArithmetic.txt
        testFiles/straight-line/literalComparisons.txt
        testFiles/straight-line/variable.txt
        testFiles/straight-line/variableArithmetic.txt
        testFiles/straight-line/variableComparisons.txt
        testFiles/straight-line/variableList.txt
        testFiles/cplusFunction.txt
        testFiles/factorialFunction.txt
        testFiles/loopIncrementFunction.txt
        testFiles/twiceFunction.txt
        arithmetic.c
        arithmetic.h
        C.flex
        C.output
        C.tab.c
        C.tab.h
        C.y
        environment.h
        git
        lex.yy.c
        log.txt
        main.c
        Makefile
        nodes.c
        nodes.h
        runBasic.ps1
        symbol_table.c
        token.h
        unitTests.ps1
        value.c
        value.h)
