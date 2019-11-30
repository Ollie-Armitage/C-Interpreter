//
// Created by ollie on 29/11/2019.
//

#include <stdio.h>
#include <interpreter/headers/value.h>
#include <Lexer_Parser_Files/token.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

VALUE* read_int();

VALUE* apply(TOKEN* name, VALUE* value){

    VALUE* answer = malloc(sizeof(VALUE));

    if(strcmp(name->lexeme, "read_int") == 0){
        read_int();
    }
    else if(strcmp(name->lexeme, "read_string") == 0){

    }
    else if(strcmp(name->lexeme, "print_string") == 0){
        printf("%s", value->v.string);
    }
    else if(strcmp(name->lexeme, "print_int") == 0){
        printf("%d", value->v.integer);
    }

    return value;

}

VALUE* read_int(){

    char x[50];
    fgets(x, 50, stdin);


}
