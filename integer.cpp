#include <iostream>

#include "integer.h"

integer::integer(int v) {
  value = v;
}

token* integer::eval() {
  //cout << "at int" << endl;
  integer* t = new integer(value);
  //t->print();
  return t;
}

void integer::print() {
  std::cout << value << endl;
}

string integer::getType() {
  return "integer";
}
