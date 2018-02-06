#include <iostream>
#include <string.h>

#include "ifstate.h"
#include "boolean.h"

ifstate::ifstate() {
  first = NULL;
  second = NULL;
  third = NULL;
}

token* ifstate::eval() {
  //cout << "at if" << endl;
  token* fvalue = first->eval();

  if (fvalue->getType().compare("boolean") != 0) {
        cerr << "Unexpected error when parsing if statement";
        exit(1);
  }
  boolean* f = dynamic_cast<boolean*>(fvalue);
  if (f->value == 't') {
    token* svalue = second->eval();
    //svalue->print();
    return svalue;
  } else {
    token* tvalue = third->eval();
    //tvalue->print();
    return tvalue;
  }
}

void ifstate::print() {
  std::cout << "if" << endl;
}

string ifstate::getType() {
  return "ifstate";
}

bool ifstate::needsChild() {
  if (first == NULL) {
    return true;
  } else if (second == NULL) {
    return true;
  } else if (third == NULL) {
    return true;
  } else {
    return false;
  }
}

token** ifstate::emptyChild() {
  if (first == NULL) {
    return &first;
  } else if (second == NULL) {
    return &second;
  } else {
    return &third;
  }
}
