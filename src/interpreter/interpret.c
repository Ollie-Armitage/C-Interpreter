#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <src/interpreter/headers/environment.h>

#include "headers/value.h"
#include "Lexer_Parser_Files/nodes.h"
#include "Lexer_Parser_Files/C.tab.h"
#include "headers/environment.h"
#include "headers/arithmetic.h"
#include "headers/debug.h"
#include "headers/interpret.h"


VALUE *interpreter(NODE *tree, ENV *e, int numberOfArgs, char **args) {

    CLOSURE* main;

    if(tree == NULL) return NULL;

    interpret(tree->left, e);

    main = get_main(e->frames);

    if(main == NULL){
        interpret(tree->right, e);
        main = get_main(e->frames);

        if(main == NULL){
            printf("Could not find main function in the global scope. Exiting.\n");
            exit(0);
        }
    }
    else{
        if(main->body == NULL){
            main->body = tree->right;
        }
    }

    VALUE* interpretation = interpret(main->body, e);

    switch(interpretation->type){
        case 0: printf("%ld\n", interpretation->v.integer); break;
        case 1:
            if(interpretation->v.boolean == 0) {
                printf("FALSE.\n");
                break;
            }
            else printf("TRUE.\n");
            break;
        case 2: printf("%s\n", interpretation->v.string);
                break;
        case 3: printf("Function returned.\n");
                break;
    }


    return NULL;
}

/* One off function using strcmp to find the function with the name "main" and return it, only searching within the
 * global scope. If it doesn't find it, it returns null.*/

CLOSURE* get_main(FRAME* frame){
    BINDING *bindings = frame->bindings;
    while (bindings != NULL) {
        if (strcmp(bindings->name->lexeme, "main") == 0) return bindings->val->v.closure;
        bindings = (BINDING *) bindings->next;
    }
    return NULL;
}

VALUE *interpret(NODE *tree, ENV *e) {

    if (tree == NULL) return NULL;

    switch (tree->type) {
        case LEAF:
            return interpret(tree->left, e);
        case '~':

            if(tree->right->type == '=') declaration_method((TOKEN*)tree->right->left->left, e->frames);
            else if (tree->right->type == ',') declaration_list_method(tree->right, e);
            else{
                declaration_method((TOKEN*)tree->right->left, e->frames);
                interpret(tree->left, e);
            }

            interpret(tree->right, e);
            break;
        case ',':
            interpret(tree->left, e);
            interpret(tree->right, e);
            break;
        case 'd':
            return interpret(tree->right, e);
        case 'D':
            return function_definition(tree, e);
        case 'F':
            return declare_function_method(tree, e);
        case ';':
            return sequence_method(tree, e);
        case IDENTIFIER:
            return name_method((TOKEN *) tree, e->frames);
        case CONSTANT: /* Use STRING_LITERAL case. */
        case STRING_LITERAL:
            return node_to_value(tree);
        case RETURN:

            return return_method(tree, e);
        case APPLY:
            return apply((TOKEN *) tree->left->left, tree->right, e);
        case IF:
            return interpret_if(tree, e);
        case '=':
            return assignment((TOKEN *) tree->left->left, e->frames, interpret(tree->right, e));
        case '+':
            //print_all_bindings(e);
            return add_method(tree->left, tree->right, e);
        case '-':
            return subtract_method(tree->left, tree->right, e);
        case '*':
            return multiply_method(tree->left, tree->right, e);
        case '/':
            return divide_method(tree->left, tree->right, e);
        case GE_OP:
            return GE_OP_method(tree->left, tree->right, e);
        case LE_OP:
            return LE_OP_method(tree->left, tree->right, e);
        case NE_OP:
            return NE_OP_method(tree->left, tree->right, e);
        case EQ_OP:
            return EQ_OP_method(tree->left, tree->right, e);
        case '<':
            return LT_method(tree->left, tree->right, e);
        case '>':
            return GT_method(tree->left, tree->right, e);

    }

    return NULL;
}

int scan_for_variable_dec(NODE* node){
    int type = node->left->left->type;

    int has_type = 0;

    switch(type){
        case INT:
        case VOID:
        case FUNCTION: has_type = 1;
        default: break;
    }

    if(has_type && node->right->left->left->type == IDENTIFIER) return 1;
    else return 0;
}

VALUE* declaration_list_method(NODE *node, ENV *e) {
    if(node->left->type == ',') declaration_list_method(node->left, e);
    else if(node->left->type == '=') declaration_method((TOKEN*)node->left->left->left, e->frames);
    if(node->right->type == 'F') declare_function_method(node->right, e);
    else if(node->right->type == LEAF) declaration_method((TOKEN*)node->right->left, e->frames);
    else if(node->right->type == '=') declaration_method((TOKEN*)node->right->left->left, e->frames);
    else printf("Unrecognized type in list.\n");
    return NULL;
}

VALUE *function_definition(NODE *tree, ENV *e) {
    VALUE* function = interpret(tree->left, e);
    function->v.closure->body = tree->right;
    return NULL;
}

/* Binds the function name to the current frame, builds an empty closure and assigns that empty closure to the
 * name, then returns the closure so the body can be bound elsewhere.*/

VALUE* declare_function_method(NODE* tree, ENV* e){
    declaration_method((TOKEN*)tree->left->left, e->frames);
    VALUE* closure = build_closure(e->frames, tree->right, NULL);
    assignment((TOKEN*)tree->left->left, e->frames, closure);
    return closure;
}

VALUE *declaration_method(TOKEN *token, FRAME *frame) {
    BINDING *bindings = frame->bindings;
    BINDING *new = malloc(sizeof(BINDING));
    if (new != 0) {
        new->name = token;
        new->val = NULL;
        new->next = (struct BINDING *) bindings;
        frame->bindings = new;
        return NULL;
    } else return NULL;
}

VALUE *name_method(TOKEN *token, FRAME *frame) {
    while (frame != NULL) {
        BINDING *bindings = frame->bindings;
        while (bindings != NULL) {
            if (bindings->name == token) return bindings->val;
            bindings = (BINDING *) bindings->next;
        }
        frame = (FRAME *) frame->next;
    }
    return NULL;
}

VALUE *build_closure(FRAME *env, NODE *ids, NODE *body) {
    VALUE *value;
    CLOSURE *closure = malloc(sizeof(CLOSURE));
    closure->env = env;
    closure->ids = ids;
    closure->body = body;
    value = make_closure_value(closure);
    return value;
}


// TODO: This function is messy and quite likely unnecessarily so; try and reduce it.

FRAME *extend_frame(ENV *env, NODE *ids, NODE *args) {

    // Build a new frame for a function and attach the current frame from the environment provided to it's end.

    FRAME *newFrame = malloc(sizeof(FRAME));
    newFrame->next = (struct FRAME *) env->frames;

    // If there are no parameters or no arguments, return the new frame empty.

    if (ids == NULL || args == NULL) return newFrame;

    NODE *ip;
    NODE *ap;

    // Do all up to the last one / two values.
    for (ip = ids, ap = args; (ip->left->type == ',' && ap->left->type == ','); ip = ip->left, ap = ap->left) {
        BINDING *newBinding = malloc(sizeof(BINDING));
        if (newBinding != 0) {
            declaration_method((TOKEN *) ip->right->right->left, newFrame);
            assignment((TOKEN *) ip->right->right->left, newFrame, interpret(ap->right, env));
            printf("Binding Allocated: %s\t Value: %ld\n", newBinding->name->lexeme, newBinding->val->v.integer);
        } else printf("Error: Binding Allocation Failed.\n");
    }

    // If two values left.

    if (ip->type == ',' && ap->type == ',') {
        BINDING *newBinding = malloc(sizeof(BINDING));
        if (newBinding != 0) {
            declaration_method((TOKEN *) ip->right->right->left, newFrame);
            assignment((TOKEN *) ip->right->right->left, newFrame, interpret(ap->right, env));
        } else printf("Error: Binding Allocation Failed.\n");

        ip = ip->left;
        ap = ap->left;
    }

    // If one left.

    BINDING *newBinding = malloc(sizeof(BINDING));
    if (newBinding != 0) {
        declaration_method((TOKEN *) ip->right->left, newFrame);
        assignment((TOKEN *) ip->right->left, newFrame, interpret(ap, env));
    } else printf("Error: Binding Allocation Failed.\n");

    // Once all the parameters have arguments bound to them, and are stored in the new frame, return the new frame.
    return newFrame;
}

VALUE *lexical_call_method(TOKEN *name, NODE *args, ENV *env) {

    ENV *tempEnv = malloc(sizeof(ENV));
    *tempEnv = *env;

    // Gets the function from the environment.
    CLOSURE *f = name_method(name, env->frames)->v.closure;

    env->frames = extend_frame(env, f->ids, args);
    env->frames->next = (struct FRAME *) f->env;

    /* Runs the function and returns its output and resets the return_answer value to 0, given it was only a return for
    a single function. */
    VALUE *answer = interpret(f->body, env);
    answer->return_answer = 0;
    *env = *tempEnv;
    free(tempEnv);
    return answer;
}

VALUE *assignment(TOKEN *token, FRAME *frame, VALUE *value) {
    while (frame != NULL) {
        BINDING *bindings = frame->bindings;
        while (bindings != NULL) {
            if (bindings->name == token){ bindings->val = value; return NULL; }
            bindings = (BINDING *) bindings->next;
        }
        frame = (FRAME *) frame->next;
    }
    return NULL;
}

VALUE *read_int() {

    VALUE *answer;
    char buffer[BUFSIZ];
    char *pointer;
    long int number;

    printf("Please enter a number: ");

    while (1) {
        if (fgets(buffer, BUFSIZ, stdin) != NULL) {
            number = strtol(buffer, &pointer, 10);
            if (buffer[0] != '\n' && (*pointer == '\n' || *pointer == '\0')) {
                answer = make_lint_value(number);
                break;
            } else printf("Invalid number entered, Please enter again: ");
        }
    }

    return answer;

}

VALUE *read_string() {
    VALUE *answer;
    char buffer[BUFSIZ];

    printf("Please enter a string: ");

    while (1) {
        if (fgets(buffer, BUFSIZ, stdin) != NULL) {
            if (buffer[0] != '\n') {
                answer = make_string_value(buffer);
                break;
            } else printf("Please enter a string: ");
        }
    }

    return answer;
}

VALUE *apply(TOKEN *name, NODE *args, ENV *e) {

    VALUE *answer = NULL;

    if (strcmp(name->lexeme, "read_int") == 0) answer = read_int();
    else if (strcmp(name->lexeme, "read_string") == 0) answer = read_string();
    else if (strcmp(name->lexeme, "print_string") == 0) printf("%s\n", interpret(args, e)->v.string);
    else if (strcmp(name->lexeme, "print_int") == 0) printf("Print_int: %ld\n", interpret(args, e)->v.integer);
    else if (strcmp(name->lexeme, "output_int_to_file") == 0) output_int_to_file(interpret(args, e)->v.integer);
    else answer = lexical_call_method(name, args, e);

    return answer;

}

void output_int_to_file(long integer) {
    FILE* file = fopen("temp", "a");
    fprintf(file, "/*%ld*/\n", integer);
    fclose(file);
}

int bind_initial_args(NODE *tree, ENV *e, char **args) {
    e->frames = extend_frame(e, tree->right, NULL);
}

/* Only when the return statement is reached is the return value set to 1, thereby indicating to anything that holds
 * the value that it should be passed back up the tree.*/

VALUE *return_method(NODE *tree, ENV *e) {
    VALUE *returnValue = interpret(tree->left, e);
    returnValue->return_answer = 1;
    return returnValue;
}

/* Run a sequence of statements. The only reason not to return the right side of the tree is if the left side is
 * the return value. If the return value has been worked out, the right side doesn't need to be run as no more
 * statements can run after the return. */

VALUE *sequence_method(NODE *tree, ENV *e) {
    VALUE *left = interpret(tree->left, e);
    if (left != NULL && left->return_answer == 1) return left;
    else free(left);
    return interpret(tree->right, e);
}

VALUE *interpret_if(NODE *tree, ENV *e) {
    if (interpret(tree->left, e)->v.boolean == 1) {
        if (tree->right->type != ELSE) return interpret(tree->right, e);
        else return interpret(tree->right->left, e);
    } else {
        if (tree->right->type != ELSE) return NULL;
        else return interpret(tree->right->right, e);
    }
}

VALUE *node_to_value(NODE *node) {

    if (node == NULL) return NULL;

    TOKEN *n = (TOKEN *) node;

    if (n->type == CONSTANT) return make_lint_value(n->value);
    else if (n->type == STRING_LITERAL) return make_string_value(n->lexeme);
    else error_exit_method("Node type invalid; cannot convert to value.");
    return NULL;
}
