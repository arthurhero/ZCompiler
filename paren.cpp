#include <iostream>

#include "paren.h"

paren::paren(char c) {
  value = c;
}

token* paren::eval() {
  return 0;
}

void paren::print() {
  std::cout << value << endl;
}

string paren::getType() {
  return "paren";
}
