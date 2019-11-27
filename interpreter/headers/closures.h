//
// Created by ollie on 26/11/2019.
//

#ifndef COMPILER_2_0_CLOSURES_H
#define COMPILER_2_0_CLOSURES_H

#include <Lexer_Parser_Files/nodes.h>
#include "environment.h"

FRAME *extend_frame(ENV *env, NODE *ids, NODE *args);

#endif //COMPILER_2_0_CLOSURES_H
