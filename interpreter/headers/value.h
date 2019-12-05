//
// Created by ollie on 05/12/2019.
//

#ifndef COMPILER_2_0_VALUE_H
#define COMPILER_2_0_VALUE_H

VALUE* make_lint_value(long integer);
VALUE* make_bool_value(int boolean);
VALUE* make_string_value(char* string);
VALUE* make_closure_value(CLOSURE* closure);


#endif //COMPILER_2_0_VALUE_H
