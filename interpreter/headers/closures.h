//
// Created by ollie on 26/11/2019.
//

#ifndef COMPILER_2_0_CLOSURES_H
#define COMPILER_2_0_CLOSURES_H


#include "environment.h"

FRAME *extend_frame(ENV *frame, NODE *ids, NODE *args);
VALUE* lexical_call_method(TOKEN* name, NODE* args, ENV* env);
VALUE* build_closure(FRAME* env, NODE* ids, NODE* body);

#endif //COMPILER_2_0_CLOSURES_H
