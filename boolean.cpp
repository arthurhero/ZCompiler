#include <iostream>

#include "boolean.h"

boolean::boolean(char c) {
  value = c;
}

token* boolean::eval(){
  boolean* t = new boolean(value);
  //cout << "at bool" << endl;
  //t->print();
  return t;
};

void boolean::print() {
  if (value == 't') {
    std::cout << "true" << endl;
  } else {
    std::cout << "false" << endl;
  }
}

string boolean::getType() {
  return "boolean";
}
