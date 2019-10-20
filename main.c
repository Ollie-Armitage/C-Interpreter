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
/*       if (tree->type=='~') { */
/*         for(i=0; i<level+2; i++) putchar(' '); */
/*         printf("%p\n", tree->left); */
/*       } */
/*       else */
        print_tree0(tree->left, level+2);
      print_tree0(tree->right, level+2);
    }
}

void print_tree(NODE *tree)
{
  print_tree0(tree, 0);
}

//--------------------------------------------------------------------------------//

VALUE* return_method(NODE* expression, ENV* e){
  return interpret(expression, e);
}

VALUE* add_method(NODE* left, NODE* right, ENV* e){ return (VALUE *)(interpret(left, e) + interpret(right, e));}

VALUE* substract_method(NODE* left, NODE* right, ENV* e){ return (VALUE *)(interpret(left, e) - interpret(right, e));}

VALUE* multiply_method(NODE* left, NODE* right, ENV* e){ return (VALUE *)(interpret(left, e) + interpret(right, e));}

VALUE* divide_method(NODE* left, NODE* right, ENV* e){ return (VALUE *)(interpret(left, e) + interpret(right, e));}

VALUE* read_int(){ int x; scanf("%d", &x); return (VALUE*)x;}

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

void error(char* string){
  printf("Error: %s\n", string);
}

void returnFunction(VALUE* value){
  if(value->type == 0){
    printf("%d\n", value->v);
  }
  else if(value->type == 1){
    if(value->v.boolean == 0){
      printf("False.\n");
    }
    else{
      printf("True.\n");
    }
  }
  else if(value->type == 2){
    printf("%s", value->v);
  }
}

VALUE* lookupVariable(TOKEN* token, FRAME* frame){
  while(frame!=NULL){
    BINDING* bindings = frame->bindings;
    while(bindings!=NULL){
      if(bindings->name == token->lexeme) return bindings->val;
      bindings = bindings->next;
    }
    frame = frame->next;
  }
  error("Unbound Variable");
}

VALUE* assignment(TOKEN* token, FRAME* frame, VALUE* value){
  printf("%s\n", token->lexeme);
  while(frame!=NULL){
    BINDING* bindings = frame->bindings;
    while(bindings!=NULL){
      if(bindings->name == token->lexeme) 
      bindings->val = value;
      return value;
    }
    frame = frame->next;
  }
  error("Assignment Failed");
}

VALUE* extendEnvBindings(TOKEN* token, FRAME* frame){
  BINDING* bindings = frame->bindings;
  BINDING* new = malloc(sizeof(BINDING));
  if(new!=0){
    new->name = token;
    new->val = (VALUE*)0;
    frame->bindings = new;
    return (VALUE*)0;
  }
}

VALUE* eval(NODE *tree, ENV *e){
  int i;
  if(tree==NULL) return;
  if(tree->type==LEAF){
    return eval(tree->left, e);
    // Left child contains an identifier (variable name), CONSTANT (number) or STRING_LITERAL (string) 
  }
  else if(tree->type==IDENTIFIER){
    // If the node is an identifier, check if the identifier exists, if not make a new variable.
    TOKEN* t = (TOKEN*)tree;
    return (VALUE*)t->lexeme;

  }
  else if(tree->type==CONSTANT || tree->type==STRING_LITERAL){
    return getNodeValue(tree);
  }
  else if(tree->type==APPLY){
    // Left child is an identifier for a FUNCTION or EXPRESSION that evaluates to a function; right child contains argument to function call.

  }
  else if(tree->type==INT || tree->type==VOID || tree->type==FUNCTION){
    //
  }
  else if(tree->type==RETURN){
    returnFunction(eval(tree->left, e));

  }
  else if(tree->type == '~'){ }
  else if(tree->type == '='){ assignment((TOKEN*)tree->left->left, e->frames, eval(tree->right, e));}
  else if(tree->type=='+'){ return add_method(tree->left, tree->right, e);}
  else if(tree->type=='-'){ return subtract_method(tree->left, tree->right, e);}
  else if(tree->type=='*'){ return multiply_method(tree->left, tree->right, e);}
  else if(tree->type=='/'){ return divide_method(tree->left, tree->right, e);}
  else if(tree->type==GE_OP){ return GEFunction(eval(tree->left, e), eval(tree->right, e));}
  else if(tree->type==LE_OP){ return LEFunction(eval(tree->left, e), eval(tree->right, e));}
  else if(tree->type==NE_OP){ return NEFunction(eval(tree->left, e), eval(tree->right, e));}
  else if(tree->type==EQ_OP){ return EQFunction(eval(tree->left, e), eval(tree->right, e));}
  else if(tree->type=='<'){ return LTFunction(eval(tree->left, e), eval(tree->right, e));}
  else if(tree->type=='>'){ return GTFunction(eval(tree->left, e), eval(tree->right, e));}
  else{
    eval(tree->left, e);
    eval(tree->right, e);
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
    eval(tree, e);
    return 0;
}
