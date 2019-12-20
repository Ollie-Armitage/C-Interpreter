#include "headers/environment.h"
#include <stdlib.h>
#include <stdio.h>

VALUE* make_value(int type){
    VALUE* answer = malloc(sizeof(VALUE));
    answer->type = type;
    answer->return_answer = 0;
    return answer;
}

VALUE* make_lint_value(long integer){
    VALUE* answer = make_value(0);
    answer->v.integer = integer;
    printf("%ld\n", integer);
    return answer;
}

VALUE* make_bool_value(int boolean){
    VALUE* answer = make_value(1);
    answer->v.boolean = boolean;
    //printf("%d\n", boolean);
    return answer;
}

VALUE* make_string_value(char* string){
    VALUE* answer = make_value(2);
    answer->v.string = string;
    //printf("%s\n", string);
    return answer;
}

VALUE* make_closure_value(CLOSURE* closure){
    VALUE* answer = make_value(3);
    answer->v.closure = closure;
    return answer;
}