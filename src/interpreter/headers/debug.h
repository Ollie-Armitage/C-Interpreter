//
// Created by ollie on 26/11/2019.
//

#ifndef COMPILER_2_0_DEBUG_H
#define COMPILER_2_0_DEBUG_H

char *named(int t);
void print_leaf(NODE *tree, int level);
void print_tree0(NODE *tree, int level);
void print_tree(NODE *tree);
void print_all_bindings(ENV* e);
void error_exit_method(char* message);

#endif //COMPILER_2_0_DEBUG_H
