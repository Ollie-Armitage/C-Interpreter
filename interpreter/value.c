//
// Created by ollie on 05/12/2019.
//

#include <interpreter/headers/environment.h>
#include <stdlib.h>

VALUE* make_value(int type){
    VALUE* answer = malloc(sizeof(VALUE));
    answer->type = type;
    answer->return_answer = 0;
    return answer;
}

VALUE* make_lint_value(long integer){
    VALUE* answer = make_value(0);
    answer->v.integer = integer;
    return answer;
}

VALUE* make_bool_value(int boolean){
    VALUE* answer = make_value(1);
    answer->v.boolean = boolean;
    return answer;
}

VALUE* make_string_value(char* string){
    VALUE* answer = make_value(2);
    answer->v.string = string;
    return answer;
}

VALUE* make_closure_value(CLOSURE* closure){
    VALUE* answer = make_value(3);
    answer->v.closure = closure;
    return answer;
}