#pragma once
#include "token.h"

class ifstate : public token {
public:
  token* first;
  token* second;
  token* third;
  token* eval();
  ifstate();
  void print();
  string getType();
  bool needsChild();
  token** emptyChild();
};
