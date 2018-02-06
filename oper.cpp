#include <iostream>
#include <string.h>

#include "oper.h"
#include "integer.h"

oper::oper(char c) {
  value = c;
  first = NULL;
  second = NULL;
}

token* oper::eval() {
  //cout << "at oper" << endl;

  token* fvalue = first->eval();
  token* svalue = second->eval();
  if (fvalue->getType().compare("integer") != 0 ||
      svalue->getType().compare("integer") !=0) {
        cerr << "Unexpected error when parsing operation: " << value;
        exit(1);
  }
  integer* f = dynamic_cast<integer*>(fvalue);
  integer* s = dynamic_cast<integer*>(svalue);
  int result;
  switch (value) {
    case '+':
    result = f -> value + s -> value;
    break;
    case '-':
    result = f -> value - s -> value;
    break;
    case '*':
    result = f -> value * s -> value;
    break;
    case '/':
    result = f -> value / s -> value;
    break;
    default :
    result = 0;
  }
  integer* t = new integer(result);
  //t->print();
  return t;
}

void oper::print() {
  std::cout << value << endl;
}

string oper::getType() {
  return "oper";
}

bool oper::needsChild() {
  if (first == NULL) {
    return true;
  } else if (second == NULL) {
    return true;
  } else {
    return false;
  }
}

token** oper::emptyChild() {
  if (first == NULL) {
    return &first;
  } else {
    return &second;
  }
}
