#include <iostream>
#include <string.h>

#include "loperator.h"
#include "integer.h"
#include "boolean.h"

loperator::loperator(string s) {
  value = s;
  first = NULL;
  second = NULL;
}

token* loperator::eval() {
  //cout << "at lo" << endl;
  token* fvalue = first->eval();
  token* svalue = second->eval();
  if (fvalue->getType().compare("integer") != 0 ||
      svalue->getType().compare("integer") != 0) {
        cerr << "Unexpected error when parsing operation: " << value;
        exit(1);
  }
  integer* f = dynamic_cast<integer*>(fvalue);
  integer* s = dynamic_cast<integer*>(svalue);
  bool result = f -> value <= s -> value;
  if (result) {
    boolean* t = new boolean('t');
    //t->print();
    return t;
  } else {
    boolean* t = new boolean('f');
    //t->print();
    return t;
  }
}

void loperator::print() {
  std::cout << "<=" << endl;
}

string loperator::getType() {
  return "loperator";
}

bool loperator::needsChild() {
  if (first == NULL) {
    return true;
  } else if (second == NULL) {
    return true;
  } else {
    return false;
  }
}

token** loperator::emptyChild() {
  if (first == NULL) {
    return &first;
  } else {
    return &second;
  }
}
