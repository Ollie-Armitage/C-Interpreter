#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include <Lexer_Parser_Files/nodes.h>
#include <Lexer_Parser_Files/token.h>
#include <Lexer_Parser_Files/C.tab.h>


#include <interpreter/types/value.h>
#include <interpreter/types/environment.h>

#include "interpreter/value.c"
#include "interpreter/conversions.c"
#include "interpreter/arithmetic.c"
#include "interpreter/bindings.c"
#include "interpreter/interpret.c"
#include "interpreter/closures.c"
