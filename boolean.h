#pragma once
#include "token.h"

class boolean : public token {
public:
  char value;
  boolean(char c);
  token* eval();
  void print();
  string getType();
};
