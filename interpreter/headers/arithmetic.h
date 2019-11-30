#ifndef COMPILER_2_0_ARITHMETIC_H
#define COMPILER_2_0_ARITHMETIC_H

VALUE* add_method(NODE* left, NODE* right, ENV* e);
VALUE* subtract_method(NODE* left, NODE* right, ENV* e);
VALUE* multiply_method(NODE* left, NODE* right, ENV* e);
VALUE* divide_method(NODE* left, NODE* right, ENV* e);
VALUE* LT_method(NODE* left, NODE* right, ENV* e);
VALUE* GT_method(NODE* left, NODE* right, ENV* e);
VALUE* NE_OP_method(NODE* left, NODE* right, ENV* e);
VALUE* EQ_OP_method(NODE* left, NODE* right, ENV* e);
VALUE* LE_OP_method(NODE* left, NODE* right, ENV* e);
VALUE* GE_OP_method(NODE* left, NODE* right, ENV* e);

#endif // COMPILER_2_0_ARITHMETIC_H