#include <stdio.h>
#include <ctype.h>
#include "nodes.h"
#include "value.h"
#include "environment.h"
#include "C.tab.h"
#include <string.h>

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

void examinePath(NODE* node){
  printf("%s\n", named(node->type));
}

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
  else{
    return "No Value.";
  }

}

int unpackValue(VALUE* value){
  if(value->type == 0){
    return value->v.integer;
  }
  else if(value->type == 1){
    return value->v.boolean;
  }
  else if(value->type == 2){
    return value->v.string;
  }
}

VALUE* packValue(type, value){
  VALUE* v = malloc(sizeof(VALUE*));

  v->type = type;
  
  
  if(type == 0){
    v->v.integer = value;
  }
  else if(type == 1){
    v->v.boolean = value;
  }
  else if(type == 2){
    v->v.string = value;
  }
  
  return v;
}

VALUE* interpret(NODE* tree, ENV* e);

VALUE* add_method(NODE* left, NODE* right, ENV* e){ return packValue(0, (unpackValue(interpret(left, e)) + unpackValue(interpret(right, e))));}

VALUE* subtract_method(NODE* left, NODE* right, ENV* e){ return packValue(0, (unpackValue(interpret(left, e)) - unpackValue(interpret(right, e))));}

VALUE* multiply_method(NODE* left, NODE* right, ENV* e){ return packValue(0, (unpackValue(interpret(left, e)) * unpackValue(interpret(right, e))));}

VALUE* divide_method(NODE* left, NODE* right, ENV* e){ return packValue(0, (unpackValue(interpret(left, e)) / unpackValue(interpret(right, e))));}

VALUE* LT_method(NODE* left, NODE* right, ENV* e){ return packValue(1, (unpackValue(interpret(left, e)) < unpackValue(interpret(right, e))));}

VALUE* GT_method(NODE* left, NODE* right, ENV* e){ return packValue(1, (unpackValue(interpret(left, e)) > unpackValue(interpret(right, e))));}

VALUE* NE_OP_method(NODE* left, NODE* right, ENV* e){ return packValue(1, (unpackValue(interpret(left, e)) != unpackValue(interpret(right, e))));}

VALUE* EQ_OP_method(NODE* left, NODE* right, ENV* e){ return packValue(1, (unpackValue(interpret(left, e)) == unpackValue(interpret(right, e))));}

VALUE* LE_OP_method(NODE* left, NODE* right, ENV* e){ return packValue(1, (unpackValue(interpret(left, e)) <= unpackValue(interpret(right, e))));}

VALUE* GE_OP_method(NODE* left, NODE* right, ENV* e){ return packValue(1, (unpackValue(interpret(left, e)) >= unpackValue(interpret(right, e))));}

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

VALUE* read_int(){ int x; scanf("%d", &x); return (VALUE*)x;}

VALUE* name_method(TOKEN* token, FRAME* frame){
  while(frame!=NULL){
    BINDING* bindings = frame->bindings;
    while(bindings!=NULL){
      if(bindings->name == token) return bindings->val;
      bindings = bindings->next;
    }
    frame = frame->next;
  }
  error("Unbound Variable");
}

VALUE* assignment(TOKEN* token, FRAME* frame, VALUE* value){
  

  while(frame!=NULL){
    BINDING* bindings = frame->bindings;
    while(bindings!=NULL){
      if(bindings->name == token) 
      bindings->val = value;
      return value;
    }
    frame = frame->next;
  }
  return NULL;
  error("Assignment Failed");
}

/* 1 - Get current bindings.
   2 - If a new binding can be memory allocated, set the bindings name to arg token, set the value to a VALUE with 0, and 

*/

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
  error("Binding Allocation Failed.\n");
}

VALUE* block_method(NODE* block, ENV* e);

void error(char* string){ printf("Error: %s\n", string);}

NODE* getNodeFromPointer(VALUE* pointerAddress){
  int* p = pointerAddress->v.integer;
  free(pointerAddress);
  return *p;
}

TOKEN* getTokenFromPointer(VALUE* pointerAddress){
  NODE* n = getNodeFromPointer(pointerAddress);
  return (TOKEN*)n;
}

VALUE* interpret(NODE *tree, ENV *e){

  if(tree==NULL) return;

  if(tree->type==LEAF){
    return interpret(tree->left, e);
    // Left child contains an identifier (variable name), CONSTANT (number) or STRING_LITERAL (string) 
  }
  else if(tree->type==IDENTIFIER){
    
    return packValue(0, &tree);
    // Return node address.
  }
  else if(tree->type==CONSTANT || tree->type==STRING_LITERAL){   
    return getNodeValue(tree);
  }
  else if(tree->type==INT || tree->type==VOID || tree->type==FUNCTION){
    return NULL;
  }
  else if(tree->type==RETURN){ return return_method(tree->left, e);}
  else if(tree->type == '~'){ declaration_method(getTokenFromPointer(interpret(tree->right, e)), e->frames);}
  else if(tree->type == '='){ 
    if(assignment(getTokenFromPointer(interpret(tree->left, e)), e->frames, interpret(tree->right, e->frames)) == NULL){
    return interpret(tree->left, e);
  }
  }
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
    printf("\nEvaluating tree...\n");
    block_method(tree, e);
    return 0;
}
