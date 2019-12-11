cmake_minimum_required(VERSION 3.15)
project(Compiler_2_0)
set(CMAKE_C_STANDARD 11)

add_library(interpreter
        arithmetic.c
        interpret.c
        debug.c
        value.c)