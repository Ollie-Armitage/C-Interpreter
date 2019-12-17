//
// Created by ollie on 17/12/2019.
//


#include <src/TAC/headers/TAC.h>

QUAD* generate(NODE* tree, ENV* e);

int generate_TAC(NODE *tree, ENV *e, char* file_directory, int debug){

    generate(tree, e);
    return 0;
}

QUAD* generate(NODE* tree, ENV* e){

    if(tree == NULL) return NULL;

    switch(tree->type){
        case LEAF:
            //return leaf_method(tree, e);
        case '~':
            //declaration_method(tree, e);
            break;
        case ',':

            break;
        case 'd':
            //return generate(tree->right, e);
        case 'D':
            //return function_definition(tree, e);
        case 'F':
            //return declare_function_method(tree, e);
        case ';':
            //return sequence_method(tree, e);
        case IDENTIFIER:
            //return name_method((TOKEN *) tree, e->frames);
        case CONSTANT: /* Use STRING_LITERAL case. */
        case STRING_LITERAL:
        case RETURN:
            //return return_method(tree, e);
        case APPLY:
            //return apply((TOKEN *) tree->left->left, tree->right, e);
        case IF:
            //return interpret_if(tree, e);
        case '=':
        case '+':
      //      return add_method(tree->left, tree->right, e);
        case '-':
     //       return subtract_method(tree->left, tree->right, e);
        case '*':
     //       return multiply_method(tree->left, tree->right, e);
        case '/':
     //       return divide_method(tree->left, tree->right, e);
        case GE_OP:
      //      return GE_OP_method(tree->left, tree->right, e);
        case LE_OP:
   //         return LE_OP_method(tree->left, tree->right, e);
        case NE_OP:
    //        return NE_OP_method(tree->left, tree->right, e);
        case EQ_OP:
   //         return EQ_OP_method(tree->left, tree->right, e);
        case '<':
     //       return LT_method(tree->left, tree->right, e);
        case '>': break;
     //       return GT_method(tree->left, tree->right, e);
    }

}

QUAD* generate_instruction(enum OP *op, TOKEN* arg1, TOKEN* arg2, TOKEN* result){
    QUAD* quad = malloc(sizeof(QUAD));
    quad->op = op;
    quad->arg1 = arg1;
    quad->arg2 = arg2;
    quad->result = result;
    return quad;
}

