#include <Lexer_Parser_Files/nodes.h>
#include <stdio.h>
#include <bits/types/FILE.h>
#include "TAC_VALUE.h"

int three_address_code(NODE* tree){
    FILE* tacOut;
    tacOut = fopen("TAC_OUT", "w");

    fclose(tacOut);

}
