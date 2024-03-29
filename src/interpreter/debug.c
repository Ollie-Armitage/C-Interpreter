#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <src/interpreter/headers/environment.h>

#include "Lexer_Parser_Files/C.tab.h"
#include "Lexer_Parser_Files/nodes.h"

char *named(int t) {
    static char b[100];
    if (isgraph(t) || t == ' ') {
        sprintf(b, "%c", t);
        return b;
    }
    switch (t) {
        default:
            return "???";
        case IDENTIFIER:
            return "id";
        case CONSTANT:
            return "constant";
        case STRING_LITERAL:
            return "string";
        case LE_OP:
            return "<=";
        case GE_OP:
            return ">=";
        case EQ_OP:
            return "==";
        case NE_OP:
            return "!=";
        case EXTERN:
            return "extern";
        case AUTO:
            return "auto";
        case INT:
            return "int";
        case VOID:
            return "void";
        case APPLY:
            return "apply";
        case LEAF:
            return "leaf";
        case IF:
            return "if";
        case ELSE:
            return "else";
        case WHILE:
            return "while";
        case CONTINUE:
            return "continue";
        case BREAK:
            return "break";
        case RETURN:
            return "return";
    }
}

void print_all_bindings(ENV* e){

    FRAME* frame = e->frames;

    while (frame != NULL) {
        BINDING *bindings = frame->bindings;
        while (bindings != NULL) {
            printf("%s:\t", bindings->name->lexeme);
            if(bindings->val != NULL){
                if(bindings->val->type == 0) printf("%ld\n", bindings->val->v.integer);
                else if(bindings->val->type == 3){
                    if (bindings->val->v.closure->body != NULL) printf("\tNOT NULL CLOSURE.\n");
                    else printf("\t NULL BY DESIGN.\n");
                }
            }
            else printf("NULL\n");


            bindings = (BINDING *) bindings->next;
        }
        frame = (FRAME *) frame->next;
    }
}

void print_leaf(NODE *tree, int level) {
    TOKEN *t = (TOKEN *) tree;
    int i;
    for (i = 0; i < level; i++) putchar(' ');
    if (t->type == CONSTANT) printf("%d (Constant)\n", t->value);
    else if (t->type == STRING_LITERAL) printf("\"%s (Literal)\"\n", t->lexeme);
    else { puts(t->lexeme); }
}

void print_tree0(NODE *tree, int level) {
    int i;
    if (tree == NULL) return;
    if (tree->type == LEAF) {
        print_leaf(tree->left, level);
    } else {
        for (i = 0; i < level; i++) putchar(' ');
        printf("%s\n", named(tree->type));

        print_tree0(tree->left, level + 2);
        print_tree0(tree->right, level + 2);
    }
}

void print_tree(NODE *tree) {
    print_tree0(tree, 0);
}

void error_exit_method(char* message){
    printf("%s\n", message);
    exit(1);
};