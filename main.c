#include <stdio.h>
#include <ctype.h>
#include "nodes.h"
#include "value.h"
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

void examineNode(NODE* node){
  printf("type: %s", named(node->type)); 
  printf(" (%d)\n", node->type);

  if(node->left){
    printf("Left Child: %s\n", named(node->left->type));
  }
  if(node->right){
    printf("Right Child: %s\n", named(node->right->type));
  }
  
  printf("Node Value (If it has one): %s\n", getNodeValue(node));

}

VALUE* addFunction(VALUE *x, VALUE *y){
  VALUE* result = malloc(sizeof(VALUE*));
  
  result->v.integer = x->v.integer + y->v.integer;
  result->type = 0;
  return result;
}

VALUE* subtractFunction(VALUE *x, VALUE *y){
  VALUE* result = malloc(sizeof(VALUE*));
  
  result->v.integer = x->v.integer - y->v.integer;
  
  result->type = 0;
  return result;
} 

VALUE* multiplyFunction(VALUE *x, VALUE *y){
  VALUE* result = malloc(sizeof(VALUE*));
  
  result->v.integer = x->v.integer * y->v.integer;
  
  result->type = 0;
  return result;
}

VALUE* divideFunction(VALUE *x, VALUE *y){
  VALUE* result = malloc(sizeof(VALUE*));
  
  result->v.integer = x->v.integer / y->v.integer;
  
  result->type = 0;
  return result;
}

VALUE* GTFunction(VALUE *x, VALUE *y){
  VALUE* result = malloc(sizeof(VALUE*));
  
  result->v.boolean = x->v.integer > y->v.integer;
  
  result->type = 1;
  return result;
}

VALUE* LTFunction(VALUE *x, VALUE *y){
  VALUE* result = malloc(sizeof(VALUE*));
  
  result->v.boolean = x->v.integer < y->v.integer;
  
  result->type = 1;
  return result;
}
VALUE* GEFunction(VALUE *x, VALUE *y){
  VALUE* result = malloc(sizeof(VALUE*));
  
  result->v.boolean = x->v.integer >= y->v.integer;
  
  result->type = 1;
  return result;
}

VALUE* LEFunction(VALUE *x, VALUE *y){
  VALUE* result = malloc(sizeof(VALUE*));
  
  result->v.boolean = x->v.integer <= y->v.integer;
  
  result->type = 1;
  return result;
}

VALUE* EQFunction(VALUE *x, VALUE *y){
  VALUE* result = malloc(sizeof(VALUE*));
  
  result->v.boolean = x->v.integer == y->v.integer;
  
  result->type = 1;
  return result;
}

VALUE* NEFunction(VALUE *x, VALUE *y){
  VALUE* result = malloc(sizeof(VALUE*));
  
  result->v.boolean = x->v.integer != y->v.integer;
  
  result->type = 1;
  return result;
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

VALUE* eval(NODE *tree){
  int i;
  if(tree==NULL) return;
  if(tree->type==LEAF){
    return eval(tree->left);
    // Left child contains an identifier (variable name), CONSTANT (number) or STRING_LITERAL (string) 
  }
  else if(tree->type==IDENTIFIER){
    // If the node is an identifier, check if the identifier exists, if not make a new variable.
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
    returnFunction(eval(tree->left));

  }
  else if(tree->type=='+'){ return addFunction(eval(tree->left), eval(tree->right));}
  else if(tree->type=='-'){ return subtractFunction(eval(tree->left), eval(tree->right));}
  else if(tree->type=='*'){ return multiplyFunction(eval(tree->left), eval(tree->right));}
  else if(tree->type=='/'){ return divideFunction(eval(tree->left), eval(tree->right));}
  else if(tree->type==GE_OP){ return GEFunction(eval(tree->left), eval(tree->right));}
  else if(tree->type==LE_OP){ return LEFunction(eval(tree->left), eval(tree->right));}
  else if(tree->type==NE_OP){ return NEFunction(eval(tree->left), eval(tree->right));}
  else if(tree->type==EQ_OP){ return EQFunction(eval(tree->left), eval(tree->right));}
  else if(tree->type=='<'){ return LTFunction(eval(tree->left), eval(tree->right));}
  else if(tree->type=='>'){ return GTFunction(eval(tree->left), eval(tree->right));}
  else{
    eval(tree->left);
    eval(tree->right);
  }
}

extern int yydebug;
extern NODE* yyparse(void);
extern NODE* ans;
extern void init_symbtable(void);

int main(int argc, char** argv)
{
    NODE* tree;
    if (argc>1 && strcmp(argv[1],"-d")==0) yydebug = 1;
    init_symbtable();
    printf("--C COMPILER\n");
    yyparse();
    tree = ans;
    printf("parse finished with %p\n", tree);
    print_tree(tree);
    printf("\nEvaluating tree...\n");
    eval(tree);
    return 0;
}
