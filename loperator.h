#pragma once
#include "token.h"

class loperator : public token {
public:
  string value;
  token* first;
  token* second;
  token* eval();
  loperator(string s);
  void print();
  string getType();
  bool needsChild();
  token** emptyChild();
};
