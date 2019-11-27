#ifndef COMPILER_2_0_NODE_H
#define COMPILER_2_0_NODE_H


#include "token.h"

typedef struct node {
  int          type;
  struct node *left;
  struct node *right;
} NODE;

NODE* make_leaf(TOKEN*);
NODE* make_node(int, NODE*, NODE*);

#endif // COMPILER_2.0_NODE_H