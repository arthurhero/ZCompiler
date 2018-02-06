#pragma once
#include "token.h"

class integer : public token {
public:
  int value;
  integer(int v);
  token* eval();
  void print();
  string getType();
};
