//
// Created by ollie on 29/11/2019.
//

#include <stdio.h>
#include <Lexer_Parser_Files/token.h>
#include <string.h>
#include <stdlib.h>
#include <Lexer_Parser_Files/nodes.h>
#include <interpreter/headers/environment.h>
#include <interpreter/headers/interpret.h>
#include "headers/closures.h"

VALUE* read_int();

VALUE* read_string();

VALUE* apply(TOKEN* name, NODE* args, ENV* e){

    VALUE* answer = malloc(sizeof(VALUE));

    if(strcmp(name->lexeme, "read_int") == 0){
        answer = read_int();
    }
    else if(strcmp(name->lexeme, "read_string") == 0){
        answer = read_string();
    }
    else if(strcmp(name->lexeme, "print_string") == 0){
        printf("%s\n", interpret(args, e)->v.string);
    }
    else if(strcmp(name->lexeme, "print_int") == 0){
        answer->v.integer = interpret(args, e)->v.integer;
        printf("Print_int: %ld\n", answer->v.integer);
    }
    else{
        answer = lexical_call_method(name, args, e);
    }



    return answer;

}

VALUE* read_int(){

    VALUE* answer = malloc(sizeof(VALUE));

    char buffer[BUFSIZ];
    char* pointer;
    long int number;

    printf("Please enter a number: ");

    while(1) {
        if (fgets(buffer, BUFSIZ, stdin) != NULL) {
            number = strtol(buffer, &pointer, 10);
            if (buffer[0] != '\n' && (*pointer == '\n' || *pointer == '\0')){
                answer->type = 0;
                answer->v.integer = number;
                break;
            }
            else printf("Invalid number entered, Please enter again: ");
        }
    }

    return answer;

}

VALUE* read_string(){
    VALUE* answer = malloc(sizeof(VALUE));

    char buffer[BUFSIZ];
    char* pointer;

    printf("Please enter a string: ");

    while(1) {
        if (fgets(buffer, BUFSIZ, stdin) != NULL) {
            if (buffer[0] != '\n'){
                answer->type = 2;
                answer->v.string = buffer;
                break;
            }
            else printf("Please enter a string: ");
        }
    }

    return answer;
}