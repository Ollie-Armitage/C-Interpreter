#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "nodes.h"
#include "C.tab.h"
#include <string.h>
#include "value.h"
#include "environment.h"
#include "value.c"
#include "arithmetic.c"


char *named(int t)
{
    static char b[100];
    if (isgraph(t) || t==' ') {
      sprintf(b, "%c", t);
      return b;
    }
    switch (t) {
      default: return "???";
    case IDENTIFIER:
      return "id";
    case CONSTANT:
      return "constant";
    case STRING_LITERAL:
      return "string";
    case LE_OP:
      return "<=";
    case GE_OP:
      return ">=";
    case EQ_OP:
      return "==";
    case NE_OP:
      return "!=";
    case EXTERN:
      return "extern";
    case AUTO:
      return "auto";
    case INT:
      return "int";
    case VOID:
      return "void";
    case APPLY:
      return "apply";
    case LEAF:
      return "leaf";
    case IF:
      return "if";
    case ELSE:
      return "else";
    case WHILE:
      return "while";
    case CONTINUE:
      return "continue";
    case BREAK:
      return "break";
    case RETURN:
      return "return";
    }
}

void print_leaf(NODE *tree, int level)
{
    TOKEN *t = (TOKEN *)tree;
    int i;
    for (i=0; i<level; i++) putchar(' ');
    if (t->type == CONSTANT) printf("%d (Constant)\n", t->value);
    else if (t->type == STRING_LITERAL) printf("\"%s (Literal)\"\n", t->lexeme);
    else if (t){ puts(t->lexeme);}
}

void print_tree0(NODE *tree, int level)
{
    int i;
    if (tree==NULL) return;
    if (tree->type==LEAF) {
      print_leaf(tree->left, level);
    }
    else {
      for(i=0; i<level; i++) putchar(' ');
      printf("%s\n", named(tree->type));

        print_tree0(tree->left, level+2);
      print_tree0(tree->right, level+2);
    }
}

void print_tree(NODE *tree)
{
  print_tree0(tree, 0);
}

//--------------------------------------------------------------------------------//

// Converts a node to a token in order to extract it's value, Returns the value.

VALUE* getNodeValue(NODE* node){
  TOKEN *n = (TOKEN *)node;
  VALUE *endValue = malloc(sizeof(VALUE*));

  if(n->type == CONSTANT){
    endValue->type = 0;
    endValue->v.integer = n->value;
    return endValue;
  }
  else if(n->type == STRING_LITERAL){
    endValue->type = 2;
    endValue->v.string = n->lexeme;
  }
}

VALUE* return_method(NODE* expression, ENV* e){ 
  VALUE* answer = interpret(expression, e);
  
  
  if(answer->type == 0){
    printf("%d\n", answer->v.integer);
  }
  else if(answer->type == 1){
    if(answer->v.boolean == 0){
      printf("False\n");
    }
    else if(answer->v.boolean == 1){
      printf("True\n");
    }
  }
  else if(answer->type == 2){
    printf("%s", answer->v.string);
  }
  else{
    printf("No valid return type.");
  }

  return interpret(expression, e);
}

VALUE* name_method(TOKEN* token, FRAME* frame){
  while(frame!=NULL){
    BINDING* bindings = frame->bindings;
    while(bindings!=NULL){
      if(bindings->name == token) return bindings->val;
      bindings = bindings->next;
    }
    frame = frame->next;
  }
  perror("Unbound Variable");
}

VALUE* assignment(TOKEN* token, FRAME* frame, VALUE* value){
  
  while(frame!=NULL){
    BINDING* bindings = frame->bindings;
    while(bindings!=NULL){
      if(bindings->name == token) bindings->val = value;
      return value;

    }
    frame = frame->next;
  }
  perror("Assignment Failed");
}

VALUE* declaration_method(TOKEN* token, FRAME* frame){
  BINDING* bindings = frame->bindings;
  BINDING* new = malloc(sizeof(BINDING));
  if(new!=0){
    new->name = token;
    new->val=(VALUE*)0;
    new->next = bindings;
    frame->bindings = new;
    return (VALUE*)0;
  }
  perror("Binding Allocation Failed.\n");
  
}

TOKEN* addressToToken(VALUE* addressValue){

  int *p = unpackStrValue(addressValue);
  
  NODE* node = malloc(sizeof(NODE*));
  node = *p;
  printf("%s\n", named(node->type));
  
  TOKEN* t = (TOKEN*)node;

  printf("inside: %s\n", t->lexeme);
  return t;
}

VALUE* nodeToAddress(NODE* tree){

  VALUE* inside_v = packValue(2, &tree);
  //printf("address: %s\n", inside_t->lexeme);
  return inside_v;
}



VALUE* block_method(NODE* block, ENV* e);

void error(char* string){ printf("Error: %s\n", string);}

VALUE* interpret(NODE *tree, ENV *e){
  if(tree==NULL) return;
  if(tree->type==LEAF){ return interpret(tree->left, e);}
  else if(tree->type == INT || tree->type == FUNCTION || tree->type == VOID){}
  else if(tree->type==IDENTIFIER){ }
  else if(tree->type==CONSTANT || tree->type==STRING_LITERAL){return getNodeValue(tree);}
  else if(tree->type==RETURN){ return return_method(tree->left, e);}
  else if(tree->type == '~'){ 
    
    VALUE* outside_v = nodeToAddress(tree->right->left->left);
    TOKEN* outside_t = addressToToken(outside_v);
    printf("%s\n", outside_t->lexeme);
  }
  else if(tree->type == '='){}
  else if(tree->type=='+'){ return add_method(tree->left, tree->right, e);}
  else if(tree->type=='-'){ return subtract_method(tree->left, tree->right, e);}
  else if(tree->type=='*'){ return multiply_method(tree->left, tree->right, e);}
  else if(tree->type=='/'){ return divide_method(tree->left, tree->right, e);}
  else if(tree->type==GE_OP){ return GE_OP_method(tree->left, tree->right, e);}
  else if(tree->type==LE_OP){ return LE_OP_method(tree->left, tree->right, e);}
  else if(tree->type==NE_OP){ return NE_OP_method(tree->left, tree->right, e);}
  else if(tree->type==EQ_OP){ return EQ_OP_method(tree->left, tree->right, e);}
  else if(tree->type=='<'){ return LT_method(tree->left, tree->right, e);}
  else if(tree->type=='>'){ return GT_method(tree->left, tree->right, e);}
  else{
    return block_method(tree->left, e);
  }
}

VALUE* block_method(NODE* block, ENV* e){
  while(block!=NULL){
    interpret(block, e);
    block = block->right;
  }
}

extern int yydebug;
extern NODE* yyparse(void);
extern NODE* ans;
extern void init_symbtable(void);

int main(int argc, char** argv)
{

    ENV* e = malloc(sizeof(ENV*));
    NODE* tree;
    if (argc>1 && strcmp(argv[1],"-d")==0) yydebug = 1;
    init_symbtable();
    printf("--C COMPILER\n");
    yyparse();
    
    tree = ans;
    printf("parse finished with %p\n", tree);
    print_tree(tree);


    printf("Press any key to continue.\n");

    printf("\nEvaluating tree...\n");
    block_method(tree, e);
    
    return 0;
}
