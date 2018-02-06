#pragma once
#include "token.h"

class paren : public token {
public:
  char value;
  paren(char c);
  token* eval();
  void print();
  string getType();
};
