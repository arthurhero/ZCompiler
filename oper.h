#pragma once
#include "token.h"

class oper : public token {
public:
  char value;
  token* first;
  token* second;
  token* eval();
  oper(char c);
  void print();
  string getType();
  bool needsChild();
  token** emptyChild();
};
