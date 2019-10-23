

VALUE* interpret(NODE* node, ENV* e);

VALUE* add_method(NODE* left, NODE* right, ENV* e){ return packValue(0, (unpackIntValue(interpret(left, e)) + unpackIntValue(interpret(right, e))));}

VALUE* subtract_method(NODE* left, NODE* right, ENV* e){ return packValue(0, (unpackIntValue(interpret(left, e)) - unpackIntValue(interpret(right, e))));}

VALUE* multiply_method(NODE* left, NODE* right, ENV* e){ return packValue(0, (unpackIntValue(interpret(left, e)) * unpackIntValue(interpret(right, e))));}

VALUE* divide_method(NODE* left, NODE* right, ENV* e){ return packValue(0, (unpackIntValue(interpret(left, e)) / unpackIntValue(interpret(right, e))));}

VALUE* LT_method(NODE* left, NODE* right, ENV* e){ return packValue(1, (unpackIntValue(interpret(left, e)) < unpackIntValue(interpret(right, e))));}

VALUE* GT_method(NODE* left, NODE* right, ENV* e){ return packValue(1, (unpackIntValue(interpret(left, e)) > unpackIntValue(interpret(right, e))));}

VALUE* NE_OP_method(NODE* left, NODE* right, ENV* e){ return packValue(1, (unpackIntValue(interpret(left, e)) != unpackIntValue(interpret(right, e))));}

VALUE* EQ_OP_method(NODE* left, NODE* right, ENV* e){ return packValue(1, (unpackIntValue(interpret(left, e)) == unpackIntValue(interpret(right, e))));}

VALUE* LE_OP_method(NODE* left, NODE* right, ENV* e){ return packValue(1, (unpackIntValue(interpret(left, e)) <= unpackIntValue(interpret(right, e))));}

VALUE* GE_OP_method(NODE* left, NODE* right, ENV* e){ return packValue(1, (unpackIntValue(interpret(left, e)) >= unpackIntValue(interpret(right, e))));}