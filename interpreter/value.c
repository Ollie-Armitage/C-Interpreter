//
// Created by ollie on 05/12/2019.
//

#include <interpreter/headers/environment.h>
#include <stdlib.h>

VALUE* make_lint_value(long integer){
    VALUE* answer = malloc(sizeof(VALUE));
    answer->type = 0;
    answer->v.integer = integer;
    return answer;
}

VALUE* make_bool_value(int boolean){
    VALUE* answer = malloc(sizeof(VALUE));
    answer->type = 1;
    answer->v.boolean = boolean;
    return answer;

}

VALUE* make_string_value(char* string){
    VALUE* answer = malloc(sizeof(VALUE));
    answer->type = 2;
    answer->v.string = string;
    return answer;
}

VALUE* make_closure_value(CLOSURE* closure){
    VALUE* answer = malloc(sizeof(VALUE));
    answer->type = 3;
    answer->v.closure = closure;
    return answer;
}